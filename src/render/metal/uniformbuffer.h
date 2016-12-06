#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Metal::UniformBuffer
	
    Metal implementation of a uniform buffer
	
	(C) 2015 See the LICENSE file.
 */
//------------------------------------------------------------------------------
#include "shading/uniformbuffer.h"
#include "types.h"
namespace JARVIS {
namespace Metal
{
class Context;
class UniformBuffer : public Base::UniformBuffer
{
    __ClassDecl(UniformBuffer);
public:
    struct LayoutMember
    {
        Core::String identifier;
        uint32 size;
    };
    
    struct UniformMember
    {
        uint32 offset;
        uint32 size;
    };
    
    /// constructor
    UniformBuffer();
    /// destructor
    virtual ~UniformBuffer();
    
    /// initialize from memory layout
    void InitWithLayout(const InitList<LayoutMember>& layout);
    /// initialize from size
    void InitWithSize(uint32 size);
    
    /// get offset of layout member
    const UniformMember& GetMember(const Core::String& name);
    /// update uniform buffer member
    void Update(const UniformMember& member, void* data, uint32 size);
    
private:
    friend class Metal::Context;
    Core::Map<Core::String, UniformMember> offsetMap;
    
    OBJC_ID_POINTER(MTLBuffer) buffer;
    uint8* mapped;
};

//------------------------------------------------------------------------------
/**
*/
inline const UniformBuffer::UniformMember&
UniformBuffer::GetMember(const Core::String &name)
{
    uint32 i = this->offsetMap.Index(name);
    j_assert(i != -1);
    return this->offsetMap.Value(i);
}

}} // namespace JARVIS::Metal