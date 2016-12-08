//------------------------------------------------------------------------------
/**
    @class JARVIS::GL4::VertexBuffer
 	(C) 2015 See the LICENSE file.
*/
#include "config.h"
#include "vertexbuffer.h"
#include "types.h"
namespace JARVIS {
namespace GL4
{
__RTTI(GL4::VertexBuffer);
//------------------------------------------------------------------------------
/**
*/
VertexBuffer::VertexBuffer()
{
    // empty
}
 
//------------------------------------------------------------------------------
/**
*/
VertexBuffer::~VertexBuffer()
{
    // empty
}

//------------------------------------------------------------------------------
/**
    Will bump the componentIndex which is then used for subsequent vertex buffers to attach their data...
    Wheeow, how will it work to cast uint32 to GLvoid* which is 64 bits...
*/
void
VertexBuffer::Bind(uint32& componentIndex)
{
    j_assert(this->handle != 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, this->handle);
    int32 i;
    for (i = 0; i < this->components.Size(); i++)
    {
        const VertexComponent& comp = this->components[i];
        glEnableVertexAttribArray(componentIndex);
        GLenum glType = Types::VertexDataType(comp.type);
        if (glType == GL_UNSIGNED_INT || glType == GL_INT || glType == GL_UNSIGNED_SHORT || glType == GL_SHORT)
        glVertexAttribIPointer(componentIndex, comp.size, glType, this->vertexByteSize, (const GLvoid*)comp.offset);
        else if (glType == GL_DOUBLE)
        glVertexAttribLPointer(componentIndex, comp.size, glType, this->vertexByteSize, (const GLvoid*)comp.offset);
        else
        glVertexAttribPointer(componentIndex, comp.size, glType, GL_FALSE, this->vertexByteSize, (const GLvoid*)comp.offset);
        componentIndex++;
    }
}

//------------------------------------------------------------------------------
/**
*/
void
VertexBuffer::InitMutable(const InitList<VertexComponent>& comps, const uint32 size, const byte* data, AccessPattern access, UsagePattern usage, FrequencyPattern frequency)
{
    Base::VertexBuffer::InitMutable(comps, size, data, access, usage, frequency);

    GLenum bufferFlags = Types::BufferUsageFlag(usage, frequency);
    glGenBuffers(1, &this->handle);
    glBindBuffer(GL_ARRAY_BUFFER, this->handle);
    glBufferData(GL_ARRAY_BUFFER, size, data, bufferFlags);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//------------------------------------------------------------------------------
/**
*/
void
VertexBuffer::InitImmutable(const InitList<VertexComponent>& comps, const uint32 size, const byte* data, AccessPattern access, UsagePattern usage, FrequencyPattern frequency, ImmutableFlags flags)
{
    Base::VertexBuffer::InitImmutable(comps, size, data, access, usage, frequency, flags);
    glGenBuffers(1, &this->handle);
    glBindBuffer(GL_ARRAY_BUFFER, this->handle);
    
#if OPENGL_VERSION_MAX >= 44
    GLenum storageFlags = StorageFlags(flags, access);
    glBufferStorage(GL_ARRAY_BUFFER, size, data, storageFlags);
#else
    GLenum bufferFlags = Types::BufferUsageFlag(usage, frequency);
    glBufferData(GL_ARRAY_BUFFER, size, data, bufferFlags);
#endif

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
}

}} // namespace JARVIS::GL4
