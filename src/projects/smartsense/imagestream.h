#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::SmartSense::ImageStream
	
    Implements an image stream, be it a file or a camera, depends on the interface being used.
	
	(C) 2015 See the LICENSE file.
*/
//------------------------------------------------------------------------------
#include "io/uri.h"
#include <opencv2/opencv.hpp>
namespace JARVIS {
namespace SmartSense
{
class ImageStream : public Core::Ref
{
    __ClassDecl(ImageStream);
public:

    enum class Capture : uint8
    {
        Video,
        Images
    };
    
    /// constructor
    ImageStream();
    /// destructor
    virtual ~ImageStream();
    
    /// setup from device number
    bool SetupVideo(uint32 dev);
    /// setup from file paths
    bool SetupImages(const Core::Array<Core::URI>& images);
    
    /// grab next image
    cv::Mat NextFrame();

public:
    Capture captureMode;
    
private:
    cv::Mat lastFrame;
    
    cv::Ptr<cv::VideoCapture> videoStream;
    Core::Array<cv::Mat> imageStream;
    uint32 currentImage;
};

}} // namespace JARVIS::SmartSense