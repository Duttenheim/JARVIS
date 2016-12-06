#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::SmartSense::Recognizer
	
    Implements a per-frame recognizer.
    
    Allows for adding named functions to a processing 
    pipeline which is then processed in a linear fashion.
    
    Also perhaps add a list of built-ins which can be retrieved without writing a function...
    
    Functions requiring a context (a marker detector for example) can
    do so by putting one in its function closure.
    
    TODO: Add the ability to fork functions.
	
	(C) 2016 See the LICENSE file.
*/
//------------------------------------------------------------------------------
#include <opencv2/opencv.hpp>
#include "functional/function.h"
namespace JARVIS {
namespace SmartSense
{
class Recognizer : public Core::Ref
{
    __ClassDecl(Recognizer);
public:

    struct IntermediateBuffer
    {
        void* buf;
        uint32 size;
        
        IntermediateBuffer() : buf(nullptr), size(0) {};
        ~IntermediateBuffer()
        {
            if (buf) Core::Memory::Free(buf);
            buf = nullptr;
        }
    };

    /// constructor
    Recognizer();
    /// destructor
    virtual ~Recognizer();
    
    /// update recognizer with new image
    void Update(const cv::Mat& mat);
    /// get result back from recognizer upon completion
    const cv::Mat& Result() const;
    
    /// add function to recognizer pipeline
    void AddToPipeline(const Core::String& name, const Ptr<Core::Function<void(const Ptr<Recognizer>& rec, cv::Mat input, cv::Mat& output)>>& func);
    
    /// register an intermediate image, this must be done for it to exist
    void RegisterIntermediate(const Core::String& name);
    /// set intermediate result in recognizer dictionary
    void SetIntermediate(const Core::String& name, cv::Mat* img);
    /// get intermediate by name
    cv::Mat* Intermediate(const Core::String& name);
    
    /// setup an intermediate data buffer with an indetermined size
    void RegisterBuffer(const Core::String& name);
    /// alloc a new buffer using name, deallocs the old one
    void AllocBuffer(const Core::String& name, uint32 size);
    /// set data in buffer and size, will copy data
    void SetBuffer(const Core::String& name, void* buf, uint32 size);
    /// get buffer by name
    const IntermediateBuffer& Buffer(const Core::String& name);
    
public:
    bool debug;
    bool isDirty;
    
private:
    Core::Array<std::tuple<Core::String, Ptr<Core::Function<void(const Ptr<Recognizer>& rec, cv::Mat input, cv::Mat& output)>>>> functions;
    Core::Map<Core::String, cv::Mat*> intermediates;
    Core::Map<Core::String, IntermediateBuffer> buffers;
    cv::Mat result;
};

//------------------------------------------------------------------------------
/**
*/
inline const cv::Mat&
Recognizer::Result() const
{
    return this->result;
}

//------------------------------------------------------------------------------
/**
*/
inline void
Recognizer::AddToPipeline(const Core::String& name, const Ptr<Core::Function<void (const Ptr<Recognizer>& rec, cv::Mat input, cv::Mat& output)>>& func)
{
    this->functions.Append(std::make_tuple(name, func));
}

//------------------------------------------------------------------------------
/**
*/
inline void
Recognizer::RegisterIntermediate(const Core::String& name)
{
    j_assert(!this->intermediates.Contains(name));
    this->intermediates.Insert(name, new cv::Mat());
}

//------------------------------------------------------------------------------
/**
*/
inline void
Recognizer::SetIntermediate(const Core::String& name, cv::Mat* img)
{
    uint32 index = this->intermediates.Index(name);
    j_assert(index != -1);
    img->copyTo(*this->intermediates.Value(index));
}

//------------------------------------------------------------------------------
/**
*/
inline cv::Mat*
Recognizer::Intermediate(const Core::String& name)
{
    return this->intermediates[name];
}

//------------------------------------------------------------------------------
/**
*/
inline void
Recognizer::RegisterBuffer(const Core::String& name)
{
    IntermediateBuffer buf;
    this->buffers.Insert(name, buf);
}

//------------------------------------------------------------------------------
/**
*/
inline void
Recognizer::AllocBuffer(const Core::String &name, uint32 size)
{
    j_assert(size > 0);
    IntermediateBuffer& buffer = this->buffers[name];
    if (buffer.buf) Core::Memory::Free(buffer.buf);
    buffer.buf = Core::Memory::Alloc(size);
    buffer.size = size;
}

//------------------------------------------------------------------------------
/**
*/
inline void
Recognizer::SetBuffer(const Core::String& name, void* buf, uint32 size)
{
    IntermediateBuffer& buffer = this->buffers[name];
    j_assert(size <= buffer.size);
    Core::Memory::Copy(buf, buffer.buf, size);
}

//------------------------------------------------------------------------------
/**
*/
inline const Recognizer::IntermediateBuffer&
Recognizer::Buffer(const Core::String &name)
{
    return this->buffers[name];
}

}} // namespace JARVIS::SmartSense