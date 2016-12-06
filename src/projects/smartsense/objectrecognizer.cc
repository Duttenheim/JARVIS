//------------------------------------------------------------------------------
/**
    @class JARVIS::SmartSense::ObjectRecognizer
 	(C) 2016 See the LICENSE file.
*/
#include "objectrecognizer.h"
namespace JARVIS {
namespace SmartSense
{
    
//------------------------------------------------------------------------------
/**
*/
ObjectRecognizer::ObjectRecognizer()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
ObjectRecognizer::~ObjectRecognizer()
{
    // empty
}

static const uint32 diludeSize = 1;
static const cv::Mat diludeElement = cv::getStructuringElement( cv::MORPH_RECT,
                                       cv::Size(2*diludeSize + 1, 2*diludeSize+1),
                                       cv::Point(diludeSize, diludeSize));
//------------------------------------------------------------------------------
/**
*/
void
ObjectRecognizer::AddReference(const cv::Mat &img)
{
    j_assert(img.data != nullptr);
    ReferenceImage ref;
    
    cv::dilate(img, img, diludeElement);
    cv::Mat blurred;
    cv::GaussianBlur(img, blurred, cv::Size(5,5), 0, 0, cv::BORDER_DEFAULT);
    cv::Mat gray;
    cv::cvtColor(blurred, gray, CV_BGR2GRAY);

    //cv::equalizeHist(gray, gray);
    cv::Mat dst;
    cv::Laplacian(gray, dst, CV_16S, 1, 2, 0, cv::BORDER_DEFAULT);
    cv::convertScaleAbs(dst, gray);
    cv::addWeighted(gray, 1.5f, gray, -0.5f, 0, ref.image);
    //cv::fastNlMeansDenoising(ref.image, ref.image, 2000);
    //cv::cvtColor(img, ref.image, CV_BGR2GRAY);
    
    cv::Ptr<cv::xfeatures2d::SURF> surf = cv::xfeatures2d::SURF::create();
    surf->detect(ref.image, ref.kp);
    surf->compute(ref.image, ref.kp, ref.desc);
    ref.desc.convertTo(ref.desc, CV_32F);
    this->matcher->add(ref.desc);
    this->references.push_back(ref);
    this->descriptors.push_back(ref.desc);
}

//------------------------------------------------------------------------------
/**
*/
void
ObjectRecognizer::Train()
{
    this->matcher->train();
}

//------------------------------------------------------------------------------
/**
*/
void
ObjectRecognizer::Open()
{
    // setup pipeline
    this->objectRecognizer = Recognizer::Create();
    
    // apply a sharpening filter to find good features
    this->objectRecognizer->RegisterIntermediate("Original");
    this->objectRecognizer->AddToPipeline("Sharpen", Core::Functional::Lambda([](
        const Ptr<Recognizer>& rec,
        cv::Mat input,
        cv::Mat& output)
    {
        rec->SetIntermediate("Original", &input);
        
        //cv::dilate(input, input, diludeElement);
        cv::Mat blurred;
        cv::GaussianBlur(input, blurred, cv::Size(5,5), 0, 0, cv::BORDER_DEFAULT);
        cv::Mat gray;
        cv::cvtColor(blurred, gray, CV_BGR2GRAY);
        //
        cv::Mat dst;
        cv::Laplacian(gray, dst, CV_16S, 1, 2, 0, cv::BORDER_DEFAULT);
        cv::convertScaleAbs(dst, gray);
        cv::addWeighted(gray, 1.5f, gray, -0.5f, 0, output);
        //cv::dilate(output, output, diludeElement);
        //cv::fastNlMeansDenoising(output, output, 20);
        //output = cv::erode(<#InputArray src#>, <#OutputArray dst#>, <#InputArray kernel#>)
        
        //cv::cvtColor(input, output, CV_BGR2GRAY);
        //rec->SetIntermediate("Edges", &output);
    }));
    
    this->surf = cv::xfeatures2d::SURF::create(400);
    const cv::Ptr<cv::flann::IndexParams>& indexParams = new cv::flann::KDTreeIndexParams(5);
    const cv::Ptr<cv::flann::SearchParams>& searchParams = new cv::flann::SearchParams(64);
    this->matcher = cv::makePtr<cv::FlannBasedMatcher>(indexParams, searchParams);
    // register intermediate image and buffer
    uint32 threshold = 50;
    uint32 distanceRatio = 2.5f;
    this->objectRecognizer->AddToPipeline("FLANN", Core::Functional::Lambda([this, threshold, distanceRatio](
        const Ptr<Recognizer>& rec,
        cv::Mat input,
        cv::Mat& output)
    {
        cv::Mat desc;
        std::vector<cv::KeyPoint> kp;
        this->surf->detect(input, kp);
        //cv::FAST(grey, kp, MaxFastMatches);
        this->surf->compute(input, kp, desc);
        
        // perform matching
        std::vector<std::vector<cv::DMatch>> matches;
        //std::vector<std::vector<cv::DMatch>> matches;
        desc.convertTo(desc, CV_32F);
        
        //output = *rec->Intermediate("Original");
        output = this->references[2].image;
        return;
            
        //matcher.knnMatch(ref.desc, desc, matches, 8);
        this->matcher->knnMatch(desc, matches, 2);
        
        //float maxDist = -FLT_MAX;
        //float minDist = FLT_MAX;
        /*
        for (uint32 j = 0; j < desc.rows; j++)
        {
            double dist = matches[j].distance;
            if (dist < minDist) minDist = dist;
            if (dist > maxDist) maxDist = dist;
        }

        

        for (uint32 j = 0; j < desc.rows; j++)
        {
            //for (int32 j = 0; j < matches[i].size(); j++)
            {
                if (matches[j].distance <= MAX(2 * minDist, 0.02f)) goodMatches.push_back(matches[j]);
            }
        }
    */
        std::vector<cv::DMatch> goodMatches;
        for (uint32 j = 0; j < matches.size(); j++)
        {
            if ((matches[j][1].distance / matches[j][0].distance) < distanceRatio) goodMatches.push_back(matches[j][0]);
            //if (matches[j][1].distance < 0.75f * matches[j][0].distance) goodMatches.push_back(matches[j][0]);
        }
        
        std::vector<uint32> imageMatches;
        std::map<uint32, std::vector<cv::Point2f>> imagePoints;
        std::map<uint32, std::vector<cv::Point2f>> referencePoints;
        imageMatches.resize(this->references.size());
        std::fill(imageMatches.begin(), imageMatches.end(), 0);
        for (uint32 j = 0; j < goodMatches.size(); j++)
        {
            imageMatches[goodMatches[j].imgIdx]++;
            imagePoints[goodMatches[j].imgIdx].push_back(kp[goodMatches[j].queryIdx].pt);
            referencePoints[goodMatches[j].imgIdx].push_back(this->references[goodMatches[j].imgIdx].kp[goodMatches[j].trainIdx].pt);
        }
        
        const cv::Scalar colors[] =
        {
            cv::Scalar(255, 0, 0),
            cv::Scalar(0, 255, 0),
            cv::Scalar(0, 0, 255),
            cv::Scalar(255, 0, 255),
            cv::Scalar(255, 255, 0),
            cv::Scalar(0, 255, 255),
            cv::Scalar(255, 255, 255),
        };
        
        std::map<uint32, std::vector<cv::Point2f>>::iterator itRef = referencePoints.begin();
        std::map<uint32, std::vector<cv::Point2f>>::iterator itObj = imagePoints.begin();
        for (; itRef != referencePoints.end() && itObj != imagePoints.end(); itRef++, itObj++)
        {
            if (imageMatches[itRef->first] < threshold) continue;
            cv::Mat H = cv::findHomography(itRef->second, itObj->second, CV_RANSAC);
            const ReferenceImage& ref = this->references[itRef->first];
            std::vector<cv::Point2f> obj_corners(4);
            obj_corners[0] = cvPoint(0,0); obj_corners[1] = cvPoint( ref.image.cols, 0 );
            obj_corners[2] = cvPoint( ref.image.cols, ref.image.rows ); obj_corners[3] = cvPoint( 0, ref.image.rows );
            std::vector<cv::Point2f> scene_corners(4);

            cv::perspectiveTransform( obj_corners, scene_corners, H);
            
            //for (uint32 ptIdx = 0; ptIdx < 4; ptIdx++) scene_corners[ptIdx] += cv::Point2f( ref.image.cols, 0);
            
            line( output, scene_corners[0], scene_corners[1], colors[itRef->first], 4 );
            line( output, scene_corners[1], scene_corners[2], colors[itRef->first], 4 );
            line( output, scene_corners[2], scene_corners[3], colors[itRef->first], 4 );
            line( output, scene_corners[3], scene_corners[0], colors[itRef->first], 4 );
        }

        /*
        for (uint32 j = 0; j < imageMatches.size(); j++)
        {
            if (imageMatches[j] >= threshold)
            {
                Core::String str = Core::String::Sprintf("Seeing image %d, with %d matches", j, imageMatches[j]);
                cv::putText(output, str.CharPtr(), cv::Point(0, (j + 1) * 10), cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar::all(255));
            }
        }*/
    }));
}

//------------------------------------------------------------------------------
/**
*/
void
ObjectRecognizer::Update(const cv::Mat &frame)
{
    this->objectRecognizer->Update(frame);
    this->surf->clear();
    cv::imshow("Capture", this->objectRecognizer->Result());
}

}} // JARVIS::SmartSense
