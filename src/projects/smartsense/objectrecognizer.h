#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::SmartSense::ObjectRecognizer
	
    Implements the pipeline which is used to detect previously known objects.
	
	(C) 2016 See the LICENSE file.
*/
//------------------------------------------------------------------------------
#include "recognizer.h"
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>
namespace JARVIS {
namespace SmartSense
{
class ObjectRecognizer : public Core::Ref
{
    __ClassDecl(ObjectRecognizer);
public:
    /// constructor
    ObjectRecognizer();
    /// destructor
    virtual ~ObjectRecognizer();
    
    /// open recognizer
    void Open();
    /// updates with new frame
    void Update(const cv::Mat& frame);
    
    /// generate reference and put into current list, adding an image here makes it tested against each time we update.
    void AddReference(const cv::Mat& img);
    /// call when you want the recognizer to begin training with the references
    void Train();
private:
    Ptr<Recognizer> objectRecognizer;
    cv::Ptr<cv::xfeatures2d::SURF> surf;
    cv::Ptr<cv::FlannBasedMatcher> matcher;
    
    struct ReferenceImage
    {
        cv::Mat image;
        cv::Mat desc;
        std::vector<cv::KeyPoint> kp;
    };
    std::vector<ReferenceImage> references;
    std::vector<cv::Mat> descriptors;
};

}} // namespace JARVIS::SmartSense