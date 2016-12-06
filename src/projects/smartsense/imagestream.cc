//------------------------------------------------------------------------------
/**
    @class JARVIS::SmartSense::ImageStream
 	(C) 2015 See the LICENSE file.
*/
#include "imagestream.h"
namespace JARVIS {
namespace SmartSense
{
    
//------------------------------------------------------------------------------
/**
*/
ImageStream::ImageStream() :
    captureMode(Capture::Video)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
ImageStream::~ImageStream()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
bool
ImageStream::SetupVideo(uint32 dev)
{
    this->captureMode = Capture::Video;
    this->videoStream = new cv::VideoCapture;
    if (this->videoStream->open(dev))
    {
        // read a single frame so we never get a 0 Mat whenever we use video.
        this->videoStream->read(this->lastFrame);
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
/**
*/
bool
ImageStream::SetupImages(const Core::Array<Core::URI>& images)
{
    this->captureMode = Capture::Images;
    this->currentImage = 0;
    this->imageStream.Clear();
    this->imageStream.Resize(images.Size());
    uint32 i;
    for (i = 0; i < images.Size(); i++)
    {
        cv::Mat image;
        image = cv::imread(images[i].LocalPath().CharPtr(), CV_LOAD_IMAGE_COLOR);
        if (image.data == nullptr) return false;
        cv::resize(image, image, cv::Size(1024, 640));
        this->imageStream.Append(image);
    }
    return true;
}

//------------------------------------------------------------------------------
/**
*/
cv::Mat
ImageStream::NextFrame()
{
    cv::Mat ret = this->lastFrame;
    if (this->captureMode == Capture::Video)
    {
        cv::Mat frame;
        if (this->videoStream->read(frame))
        {
            cv::resize(frame, ret, cv::Size(1024, 640));
            this->lastFrame = ret;
        }
    }
    else if (this->captureMode == Capture::Images)
    {
        ret = this->imageStream[this->currentImage];
        this->lastFrame = ret;
        this->currentImage = (this->currentImage + 1) % this->imageStream.Size();
    }

    return ret;
}

}} // namespace JARVIS::SmartSense
