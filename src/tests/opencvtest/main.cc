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
        cv::namedWindow("Control", cv::WINDOW_AUTOSIZE|CV_GUI_EXPANDED);
        cv::namedWindow("Original", cv::WINDOW_AUTOSIZE|CV_GUI_EXPANDED);

        cv::Mat edges;
        cap >> edges;
        cv::Mat lines;
        for (;;)
        {
            cv::Mat frame;
            cap >> frame;
#if (1)
            std::vector<std::vector<cv::Point>> contours;
            std::vector<cv::Vec4i> hierarchy;
            
            cv::cvtColor(frame, edges, CV_BGR2GRAY);
            
            cv::Canny(edges, edges, 100, 200);
            cv::findContours(edges, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
            lines = cv::Mat::zeros(edges.size(), CV_8UC3);
            for (int i = 0; i < contours.size(); i++)
            {
                std::vector<cv::Point> shape;
                cv::approxPolyDP(contours[i], shape, 3, true);
                //if (shape.size() == 3)
                {
                    cv::drawContours(lines, contours, i, cv::Scalar(0, 0, 255));
                    //cv::putText(lines, "Triangle", shape[0], cv::FONT_HERSHEY_PLAIN, 0.8, cv::Scalar(200,200,250), 1, CV_AA);
                }
            }
#else
            int minHessian = 100;
            cv::SurfFeatureDetector detector(minHessian);
#endif

            cv::imshow("Control", edges);
            cv::imshow("Original", frame + lines);
            
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
