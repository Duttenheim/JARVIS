#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::SmartSense::MovementTracker
	
    Implements the movement tracker pipeline.
	
	(C) 2016 See the LICENSE file.
*/
//------------------------------------------------------------------------------
#include "recognizer.h"
namespace JARVIS {
namespace SmartSense
{
class MovementTracker : public Core::Ref
{
    __ClassDecl(MovementTracker);
public:
    /// constructor
    MovementTracker();
    /// destructor
    virtual ~MovementTracker();
    
    /// opens the tracker
    void Open();
    
    /// updates with new frame
    void Update(const cv::Mat& frame);
    
private:

    Ptr<Recognizer> detector;
    Ptr<Recognizer> tracker;
};

}} // namespace JARVIS::SmartSense