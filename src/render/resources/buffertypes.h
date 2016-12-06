#pragma once
//------------------------------------------------------------------------------
//  @file resources/buffertypes.h
//	(C) 2015 See the LICENSE file.
//------------------------------------------------------------------------------

namespace JARVIS {
namespace Render
{

enum class BufferType : uint8
{
    IndexBufferType,
    VertexBufferType,
    UniformBufferType,
    StorageBufferType,
    FeedbackBufferType,
    DrawBufferType,
    CommandBufferType
};

enum class StorageType : uint8
{
    Initial,            // data storage is not setup yet
    Mutable,            // data storage can be resized and changed
    Immutable           // data storage can only be updated with new data
};

// used to describe how data is accessed when buffer is mapped
enum class AccessPattern : uint8
{
    None,
    Read,
    Write,
    ReadWrite
};

// used by the implementation to determine what the buffer is to be used for
enum class UsagePattern : uint8
{
    Undefined,
    CPUWriteGPURead,    // write from CPU to GPU, and use on GPU
    CPUReadGPUWrite,    // read to CPU from GPU, and let GPU modify
    GPUReadGPUWrite     // keep read and writes entirely on GPU
};

// used to determine with which frequency a buffer is to be used
enum class FrequencyPattern : uint8
{
    Undefined,
    ChangeOnceUseMany,  // buffer once, then use for the rest of the application
    ChangeOnceUseFew,   // buffer once, and use a finite number of times
    ChangeManyUseMany   // buffer and use with equal frequency
};

// used for immutable buffers
enum ImmutableFlags : uint8
{
    None = 0,
    Coherent = 1 << 0,          // allow the buffer to be coherent with driver memory
    Persistent = 1 << 1,        // allow the buffer to be mapped once and used several times
    DynamicStorage = 1 << 2     // allow a buffer using the above flags to be dynamically updated
};

}} // namespace JARVIS::Render