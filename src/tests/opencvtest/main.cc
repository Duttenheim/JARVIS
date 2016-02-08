//------------------------------------------------------------------------------
/**
    @file opencvtest/main.cc
    
	Main entry point for opencv testing.
	
	(C) 2015 See the LICENSE file.
*/
#include "config.h"
#define NULL 0
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>
#define NULL nullptr_t

using namespace JARVIS::Core;

template <class T>
using cvPtr = cv::Ptr<T>;

struct Reference
{
    cv::Mat image;
    cv::Mat desc;
    std::vector<cv::KeyPoint> kp;
};

const uint32 MaxNumMatches = 100;
const uint32 MaxFastMatches = 20;
void FLANNMatch(const Reference& ref, cv::Mat& stream, const int32 threshold, cv::Mat& output, const cv::FlannBasedMatcher& matcher)
{
    //cvPtr<cv::xfeatures2d::FREAK> detector = cv::xfeatures2d::FREAK::create();
    std::vector<cv::KeyPoint> kp;

    cv::Mat desc;
    cvPtr<cv::xfeatures2d::SURF> surf = cv::xfeatures2d::SURF::create();
    surf->detect(stream, kp);
    //cv::FAST(grey, kp, MaxFastMatches);
    surf->compute(stream, kp, desc);
    
    // perform matching
    std::vector<cv::DMatch> matches;
    //std::vector<std::vector<cv::DMatch>> matches;
    desc.convertTo(desc, CV_32F);
    //matcher.knnMatch(ref.desc, desc, matches, 8);
    matcher.match(ref.desc, desc, matches);
    
    float maxDist = 0;
    float minDist = 10;
    for (uint32 i = 0; i < matches.size(); i++)
    {
        //for (uint j = 0; j < matches[i].size(); j++)
        {
            float dist = matches[i].distance;
            if (dist < minDist) minDist = dist;
            if (dist > maxDist) maxDist = dist;
        }
    }
    
    std::vector<cv::DMatch> goodMatches;
    for (int32 i = 0; i < matches.size(); i++)
    {
        //for (int32 j = 0; j < matches[i].size(); j++)
        {
            if (matches[i].distance <= MAX(2 * minDist, 0.02f)) goodMatches.push_back(matches[i]);
        }
    }
    
    // check if within threshold
    if (goodMatches.size() >= threshold)
    {
        cv::Point center(stream.cols/2, stream.rows/2);
        cv::String msg = cv::format("I see you O_O!", goodMatches.size());
        //cv::drawMatches(ref.image, ref.kp, stream, kp, goodMatches, output, cv::Scalar::all(-1), cv::Scalar::all(-1), std::vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
        stream.copyTo(output);
        cv::putText(output, msg, center, cv::FONT_HERSHEY_SCRIPT_SIMPLEX, 1, cv::Scalar::all(255));
        //cv::putText(output, "Seeing the object!", center, cv::FONT_HERSHEY_SCRIPT_SIMPLEX, 1, cv::Scalar::all(255));
        //cv::drawMatches(cv::noArray(), kp1, stream, kp2, matches, output);
        //cv::drawKeypoints(stream, kp2, output);
    }
    else
    {
        stream.copyTo(output);
    }
}

void
GenerateReference(const cv::Mat& img, Reference& out)
{
    //cvPtr<cv::xfeatures2d::FREAK> detector = cv::xfeatures2d::FREAK::create();
    cv::cvtColor(img, out.image, CV_BGRA2GRAY);
    cvPtr<cv::xfeatures2d::SURF> surf = cv::xfeatures2d::SURF::create();
    surf->detect(out.image, out.kp);
    surf->compute(out.image, out.kp, out.desc);
    out.desc.convertTo(out.desc, CV_32F);
}

JARVIS_MAIN
{
    // open default video device
    cv::VideoCapture cap(0);
    
    if (cap.isOpened())
    {
        cv::namedWindow("Original", cv::WINDOW_AUTOSIZE|CV_GUI_EXPANDED);

        // generate result frame
        cv::Mat initFrame;
        cap >> initFrame;
        cv::Mat res = cv::Mat(initFrame.cols, initFrame.rows, CV_8UC3, cv::Scalar(0));
        
        // generate reference
        cv::Mat ref = cv::imread("opencv-example-image.png", CV_LOAD_IMAGE_COLOR);
        Reference refObj;
        GenerateReference(ref, refObj);
        
        cv::FlannBasedMatcher matcher;
        cvPtr<cv::BackgroundSubtractorMOG2> backgroundRemover = cv::createBackgroundSubtractorMOG2();
        for (;;)
        {
            cv::Mat frame;
            cap >> frame;
            cv::Mat mask;
            
            // generate new reference if we press f
            if (cv::waitKey(30) == 'f')
            {
                GenerateReference(frame, refObj);
            }
            
            // apply background remover
            //backgroundRemover->apply(frame, mask);
            
            // convert to grey and apply mask
            cv::Mat grey;
            cv::cvtColor(frame, grey, CV_BGR2GRAY);
            //cv::bitwise_and(grey, mask, frame);
            
            FLANNMatch(refObj, GREY, 70, res, matcher);
            cv::imshow("Original", res);
            
            if (cv::waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
            {
                printf("Exiting");
                break;
            }
        }
    }

    cv::waitKey(0);
   	return 0;
}
