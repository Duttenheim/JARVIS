//------------------------------------------------------------------------------
/**
    @class JARVIS::SmartSense::Recognizer
 	(C) 2016 See the LICENSE file.
*/
#include "recognizer.h"
namespace JARVIS {
namespace SmartSense
{
    
//------------------------------------------------------------------------------
/**
*/
Recognizer::Recognizer() :
    debug(false),
    isDirty(true)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
Recognizer::~Recognizer()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
void
Recognizer::Update(const cv::Mat& mat)
{
    this->result = mat;

    uint32 i;
    for (i = 0; i < this->functions.Size(); i++)
    {
        cv::Mat output;
        std::get<1>(this->functions[i])->Call(this, this->result, output);
        this->result = output;
        
        if (this->debug)
        {
            Core::String debugName = Core::String::Sprintf("Debug '%s'", std::get<0>(this->functions[i]).CharPtr());
            cv::imshow(debugName.CharPtr(), output);
        }
    }
    
    this->isDirty = false;
}

}} // JARVIS::SmartSense
