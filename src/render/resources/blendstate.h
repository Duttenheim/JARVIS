#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Render::BlendState
	
    Encapsulates a blend state, but is only usable when constructing a pipeline state.
	
	(C) 2015 See the LICENSE file.
*/
//------------------------------------------------------------------------------
namespace JARVIS {
namespace Render
{
struct BlendState
{
public:

    /// constructor
    BlendState() : colorBlendOp(BlendOp::Add), alphaBlendOp(BlendOp::Add), srcColorBlendMode(BlendMode::One), dstColorBlendMode(BlendMode::Zero), srcAlphaBlendMode(BlendMode::One), dstAlphaBlendMode(BlendMode::Zero), blendEnabled(false) {}
    /// construct from nullptr, basically run base constructor
    BlendState(std::nullptr_t) : BlendState() {};

    enum class BlendOp : uint8
    {
        Add,
        Subtract,
        InvSubtract,
        Min,
        Max
    };
    
    enum class BlendMode : uint8
    {
        Zero,
        One,
        SourceColor,
        OneMinusSourceColor,
        SourceAlpha,
        OneMinusSourceAlpha,
        DestinationColor,
        OneMinusDestinationColor,
        DestinationAlpha,
        OneMinusDestinationAlpha,
        SourceAlphaSaturated,
        BlendColor,
        OneMinusBlendColor,
        BlendAlpha,
        OneMinusBlendAlpha
    };

    BlendOp colorBlendOp;
    BlendOp alphaBlendOp;
    BlendMode srcColorBlendMode;
    BlendMode dstColorBlendMode;
    BlendMode srcAlphaBlendMode;
    BlendMode dstAlphaBlendMode;
    bool blendEnabled;
    
};

}} // namespace JARVIS::Render