//------------------------------------------------------------------------------
/**
    @file opencvtest/main.cc
    
	Main entry point for opencv testing.
	
	(C) 2015 See the LICENSE file.
*/
#include "config.h"
#include <opencv2/opencv.hpp>

using namespace JARVIS::Core;

JARVIS_MAIN
{
    // open default video device
    cv::VideoCapture cap(0);
    
    if (cap.isOpened())
    {
        cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE);
        
        cv::Mat edges;
        for (;;)
        {
            cv::Mat frame;
            cap >> frame;
            
            cv::cvtColor(frame, edges, CV_BGR2GRAY);
            cv::GaussianBlur(edges, edges, cv::Size(3,3), 1);
            cv::Laplacian(edges, edges, CV_8U, 3);//(edges, edges, CV_8U, 1, 1, 1);
            //cv::Canny(edges, edges, 0, 30, 3);
            cv::imshow("Display Image", edges);
        }
    }
    //cv::imshow("Display Image", image);

    cv::waitKey(0);
   	return 0;
}
