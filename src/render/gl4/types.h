#pragma once
//------------------------------------------------------------------------------
//  @file gl4/types.h
//	(C) 2015 See the LICENSE file.
//------------------------------------------------------------------------------

namespace JARVIS {
namespace GL4 {
namespace Types {

using UsagePattern = Base::Buffer::UsagePattern;
using FrequencyPattern = Base::Buffer::FrequencyPattern;
using ImmutableFlags = Base::Buffer::ImmutableFlags;
using AccessPattern = Base::Buffer::AccessPattern;
using ComponentType = VertexBuffer::VertexComponent::ComponentType;

//------------------------------------------------------------------------------
/**
*/
inline GLenum
BufferUsageFlag(const UsagePattern usage, const FrequencyPattern frequency)
{
    GLenum bufferUsage = 0;
    switch (usage)
    {
        case UsagePattern::CPUReadGPUWrite:
            switch (frequency)
            {
                case FrequencyPattern::ChangeOnceUseMany:
                    bufferUsage = GL_STATIC_READ;
                    break;
                case FrequencyPattern::ChangeOnceUseFew:
                    bufferUsage = GL_STREAM_READ;
                    break;
                case FrequencyPattern::ChangeManyUseMany:
                    bufferUsage = GL_DYNAMIC_READ;
                    break;
                case FrequencyPattern::Undefined:
                    j_error("GL4::Types::BufferUsageFlag() : Undefined frequency pattern is not allowed!");
                    break;
            }
            break;
        case UsagePattern::CPUWriteGPURead:
            switch (frequency)
            {
                case FrequencyPattern::ChangeOnceUseMany:
                    bufferUsage = GL_STATIC_DRAW;
                    break;
                case FrequencyPattern::ChangeOnceUseFew:
                    bufferUsage = GL_STREAM_DRAW;
                    break;
                case FrequencyPattern::ChangeManyUseMany:
                    bufferUsage = GL_DYNAMIC_DRAW;
                    break;
                case FrequencyPattern::Undefined:
                    j_error("GL4::Types::BufferUsageFlag() : Undefined frequency pattern is not allowed!");
                    break;
            }
            break;
        case UsagePattern::GPUReadGPUWrite:
            switch (frequency)
            {
                case FrequencyPattern::ChangeOnceUseMany:
                    bufferUsage = GL_STATIC_COPY;
                    break;
                case FrequencyPattern::ChangeOnceUseFew:
                    bufferUsage = GL_STREAM_COPY;
                    break;
                case FrequencyPattern::ChangeManyUseMany:
                    bufferUsage = GL_DYNAMIC_COPY;
                    break;
                case FrequencyPattern::Undefined:
                    j_error("GL4::Types::BufferUsageFlag() : Undefined frequency pattern is not allowed!");
                    break;
            }
            break;
        case UsagePattern::Undefined:
            j_error("GL4::Types::BufferUsageFlag() : Undefined usage pattern is not allowed!");
            break;
    }
    return bufferUsage;
}

//------------------------------------------------------------------------------
/**
*/
inline GLenum
StorageFlag(const ImmutableFlags flags, const AccessPattern access)
{
    GLenum res = 0;
    switch (flags)
    {
        case ImmutableFlags::Coherent: res |= GL_MAP_COHERENT_BIT;
            break;
        case ImmutableFlags::DynamicStorage: res |= GL_DYNAMIC_STORAGE_BIT;
            break;
        case ImmutableFlags::Persistent: res |= GL_MAP_PERSISTENT_BIT;
            break;
        case ImmutableFlags::None:
            break;
    }
    
    switch (access)
    {
        case AccessPattern::Read: res |= GL_MAP_READ_BIT;
            break;
        case AccessPattern::Write: res |= GL_MAP_WRITE_BIT;
            break;
        case AccessPattern::ReadWrite: res |= GL_MAP_READ_BIT | GL_MAP_WRITE_BIT;
            break;
        case AccessPattern::None:
            break;
    }
    return res;
}

//------------------------------------------------------------------------------
/**
*/
inline GLenum
VertexDataType(ComponentType type)
{
    switch (type)
    {
        case ComponentType::UByte: return GL_UNSIGNED_BYTE;
        case ComponentType::Byte: return GL_BYTE;
        case ComponentType::UInt: return GL_UNSIGNED_INT;
        case ComponentType::Int: return GL_INT;
        case ComponentType::UShort: return GL_UNSIGNED_SHORT;
        case ComponentType::Short: return GL_SHORT;
        case ComponentType::Float: return GL_FLOAT;
        case ComponentType::Double: return GL_DOUBLE;
    }
}

}}} // namespace JARVIS::GL4::Types