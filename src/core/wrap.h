#pragma once
//------------------------------------------------------------------------------
//  @file core/wrap.h
//	(C) 2016 See the LICENSE file.
//------------------------------------------------------------------------------

// It's a wrap!
#define __Wrap(ns, ins, cls) \
namespace JARVIS { \
namespace ns { \
class cls : public JARVIS::ins::cls {}; \
__Ptr(cls); \
}}