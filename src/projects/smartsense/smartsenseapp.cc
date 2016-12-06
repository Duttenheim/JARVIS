//------------------------------------------------------------------------------
/**
    @class JARVIS::SmartSense::SmartSenseApp
 	(C) 2015 See the LICENSE file.
*/
#include "smartsenseapp.h"
#include "io/assigns.h"
#include "functional/function.h"
#include <opencv2/xfeatures2d.hpp>
namespace JARVIS {
namespace SmartSense
{
    
//------------------------------------------------------------------------------
/**
*/
SmartSenseApp::SmartSenseApp() :
    frameCounter(0)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
SmartSenseApp::~SmartSenseApp()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
void
SmartSenseApp::OnSetup()
{
    Application::OnSetup();
    
    if (this->args.Flag("-help"))
    {
        printf("SmartSense Application Help menu: \n\
            -mode (video/images) selects between the two different capturing methods. \n\
            -help displays this menu.\n\n");
        this->Stop();
    }
    
    // setup new image stream from provided images.
    this->stream = ImageStream::Create();
    
    if (this->args.Flag("-mode"))
    {
        const Core::String& mode = this->args.Value("-mode");
        if (mode == "video")
        {
            this->stream->SetupVideo(0);
        }
        else if (mode == "images")
        {
            this->stream->SetupImages({
                "root:data/Rotation/Nord.jpg",
                "root:data/Rotation/NordOst.jpg",
                "root:data/Rotation/Ost.jpg",
                "root:data/Rotation/SydOst.jpg",
                "root:data/Rotation/Syd.jpg"});
        }
        else
        {
            j_error("Invalid capture mode '%s'\n", mode.CharPtr());
        }
    }
    else
    {
        this->stream->SetupImages({
            "root:data/Translation/WP_20160122_003.jpg",
            "root:data/Translation/WP_20160122_004.jpg",
            "root:data/Translation/WP_20160122_005.jpg",
            "root:data/Translation/WP_20160122_006.jpg",
            "root:data/Translation/WP_20160122_007.jpg"});
    }
    
    // setup new tracker
    this->tracker = Recognizer::Create();
    this->tracker->SetDebug(true);
    
    // setup new recognizer
    this->detector = Recognizer::Create();
    this->detector->RegisterIntermediate("Original");
    this->detector->RegisterIntermediate("Edges");
    
    // apply a sharpening filter to find good features
    this->detector->AddToPipeline("Sharpen", Core::Functional::Lambda([](
        const Ptr<Recognizer>& rec,
        cv::Mat input,
        cv::Mat& output)
    {
        cv::Mat blurred;
        cv::GaussianBlur(input, blurred, cv::Size(5,5), 0, 0, cv::BORDER_DEFAULT);
        cv::Mat gray;
        cv::cvtColor(blurred, gray, CV_BGR2GRAY);
        cv::Mat dst;
        cv::Laplacian(gray, dst, CV_16S, 1, 2, 0, cv::BORDER_DEFAULT);
        cv::convertScaleAbs(dst, blurred);
        cv::addWeighted(blurred, 1.5f, gray, -0.5f, 0, output);
        rec->SetIntermediate("Original", &input);
        rec->SetIntermediate("Edges", &output);

    }));
    
    // register intermediate image and buffer
    this->detector->RegisterIntermediate("LastFrame");
    this->detector->RegisterBuffer("Corners");
    uint32 threshold = 200;
    this->detector->AddToPipeline("Corners", Core::Functional::Lambda([threshold](
        const Ptr<Recognizer>& rec,
        cv::Mat input,
        cv::Mat& output)
    {
        std::vector<cv::Point2f> corners;
        double quality = 0.04;
        double minDist = 10;
        int blockSize = 4;
        bool useHarris = true;
        double k = 0.04;
        const int numCorners = 10;
    
        output = *rec->Intermediate("Original");
        
        // create tracking points
        cv::goodFeaturesToTrack(input, corners, numCorners, quality, minDist, cv::Mat(), blockSize, useHarris, k);
        
        // save corners
        rec->AllocBuffer("Corners", corners.size() * sizeof(cv::Point2f));
        rec->SetBuffer("Corners", &corners[0], corners.size() * sizeof(cv::Point2f));
    }));
    
    uint32 pointThreshold = 3;
    uint32 distanceThreshold = 40;
    this->tracker->AddToPipeline("Track", Core::Functional::Lambda([this, pointThreshold, distanceThreshold](
        const Ptr<Recognizer>& rec,
        cv::Mat input,
        cv::Mat& output)
    {
        const Ptr<Recognizer>& detector = this->detector;
        cv::Mat* prev = detector->Intermediate("Original");

        // hmm, get scratch buffer and convert to std::vector...
        const Recognizer::IntermediateBuffer& points = detector->Buffer("Corners");
        std::vector<cv::Point2f> prevPoints;
        uint32 numPoints = points.size / sizeof(cv::Point2f);
        uint32 pointIdx;
        cv::Point2f* data = (cv::Point2f*)points.buf;
        prevPoints.reserve(numPoints);
        for (pointIdx = 0; pointIdx < numPoints; pointIdx++)
        {
            prevPoints.push_back(data[pointIdx]);
        }
        
        // setup output from optical flow algorithm
        std::vector<cv::Point2f> corners;
        cv::Mat err;
        std::vector<ubyte> status;
        cv::calcOpticalFlowPyrLK(*prev, input, prevPoints, corners, status, err);
        
        // copy original image
        output = input;
        
        uint32 validPoints = 0;
        int r = 4;
        for(uint32 i = 0; i < corners.size(); i++)
        {
            // if point is tracked and the distance is within some threshhold we denote this as a small movement
            if (status[i] == 1 && cv::norm(corners[i] - prevPoints[i]) < distanceThreshold)
            {
                if (rec->Debug())
                {
                    cv::circle(output, corners[i], r, cv::Scalar(0, 0, 255));
                    cv::line(output, corners[i], prevPoints[i], cv::Scalar(0, 255, 0));
                }
                validPoints++;
            }
        }
        if (validPoints < pointThreshold) detector->SetNeedsUpdate(true);
    }));
    
    // create window preempively
    cv::namedWindow("Image", cv::WINDOW_AUTOSIZE);
}

//------------------------------------------------------------------------------
/**
*/
void
SmartSenseApp::OnFrame()
{
    uint32 wait = 0;
    cv::Mat frame;
    frame = this->stream->NextFrame();
    if (this->stream->CaptureMode() == ImageStream::Capture::Video)
    {
        // if we use video, wait 30 ms between each grab
        wait = 30;
    }
    
    // update recognizer
    if (this->detector->NeedsUpdate())
    {
        // we have moved since our points doesn't match anymore!
        this->detector->Update(frame);
        printf("Movement!\n");
    }
    this->tracker->Update(frame);
    cv::imshow("Capture", this->tracker->Result());
    
    // perform wait, this is needed by OpenCV to update shizzle.
    uint8 result = cv::waitKey(wait);
    if (result == '\e') this->Stop();
    frameCounter++;
}

//------------------------------------------------------------------------------
/**
*/
void
SmartSenseApp::OnExit()
{
    cv::destroyWindow("Image");
    this->stream = nullptr;
    this->detector = nullptr;
    this->tracker = nullptr;
}

}} // namespace JARVIS::SmartSense
