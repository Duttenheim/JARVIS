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
    
    // setup movement tracker
    this->movementTracker = MovementTracker::Create();
    this->movementTracker->Open();
    
    // setup object recognizer
    this->objectRecognizer = ObjectRecognizer::Create();
    this->objectRecognizer->Open();
    
    Core::URI book("root:data/book1.jpg");
    this->objectRecognizer->AddReference(cv::imread(book.LocalPath().CharPtr(), CV_LOAD_IMAGE_COLOR));
    book.Set("root:data/book2.jpg");
    this->objectRecognizer->AddReference(cv::imread(book.LocalPath().CharPtr(), CV_LOAD_IMAGE_COLOR));
    book.Set("root:data/book3.jpg");
    this->objectRecognizer->AddReference(cv::imread(book.LocalPath().CharPtr(), CV_LOAD_IMAGE_COLOR));
    this->objectRecognizer->Train();
    
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
    if (this->stream->captureMode == ImageStream::Capture::Video)
    {
        // if we use video, wait 30 ms between each grab
        wait = 30;
    }
    
    //this->movementTracker->Update(frame);
    this->objectRecognizer->Update(frame);
    
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
    this->movementTracker = nullptr;
    this->objectRecognizer = nullptr;
}

}} // namespace JARVIS::SmartSense
