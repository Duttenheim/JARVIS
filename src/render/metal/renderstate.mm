//------------------------------------------------------------------------------
/**
    @class JARVIS::Metal::RenderState
 	(C) 2015 See the LICENSE file.
*/
#include "renderstate.h"
#include "types.h"
#include "../context.h"
namespace JARVIS {
namespace Metal
{
    
//------------------------------------------------------------------------------
/**
*/
RenderState::RenderState() :
    Base::RenderState(),
    mtlDepthStencilState(nullptr),
    mtlScissorRect(nullptr)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
RenderState::~RenderState()
{
    // empty
}

//------------------------------------------------------------------------------
/**
    Apply changes in Metal
*/
void
RenderState::Commit()
{
    if (this->mtlScissorRect != nullptr) delete this->mtlScissorRect;
    this->mtlScissorRect = new MTLScissorRect;
    this->mtlScissorRect->x = this->scissorRect.x();
    this->mtlScissorRect->y = this->scissorRect.y();
    this->mtlScissorRect->width = this->scissorRect.z();
    this->mtlScissorRect->height = this->scissorRect.w();
    
    MTLDepthStencilDescriptor* desc = [[MTLDepthStencilDescriptor alloc] init];
    desc.depthCompareFunction = Types::CompareModeFlag(this->depthCompare);
    desc.depthWriteEnabled = this->depthWrite;
    
    // set back face stencil stuff
    desc.backFaceStencil = [[MTLStencilDescriptor alloc] init];
    desc.backFaceStencil.stencilFailureOperation = Types::StencilOpFlag(this->backFaceStencil.sfail);
    desc.backFaceStencil.depthFailureOperation = Types::StencilOpFlag(this->backFaceStencil.dfail);
    desc.backFaceStencil.depthStencilPassOperation = Types::StencilOpFlag(this->backFaceStencil.dspass);
    desc.backFaceStencil.stencilCompareFunction = Types::CompareModeFlag(this->backFaceStencil.compareMode);
    desc.backFaceStencil.readMask = this->backFaceStencil.readMask;
    desc.backFaceStencil.writeMask = this->backFaceStencil.writeMask;
    
    // set front face stencil stuff
    desc.frontFaceStencil = [[MTLStencilDescriptor alloc] init];
    desc.frontFaceStencil.stencilFailureOperation = Types::StencilOpFlag(this->frontFaceStencil.sfail);
    desc.frontFaceStencil.depthFailureOperation = Types::StencilOpFlag(this->frontFaceStencil.dfail);
    desc.frontFaceStencil.depthStencilPassOperation = Types::StencilOpFlag(this->frontFaceStencil.dspass);
    desc.frontFaceStencil.stencilCompareFunction = Types::CompareModeFlag(this->frontFaceStencil.compareMode);
    desc.frontFaceStencil.readMask = this->frontFaceStencil.readMask;
    desc.frontFaceStencil.writeMask = this->frontFaceStencil.writeMask;

    // create state
    this->mtlDepthStencilState = [Render::Context::Current->device newDepthStencilStateWithDescriptor:desc];
    
    // end change in base class
    Base::RenderState::Commit();
}

}} // namespace JARVIS::Metal
