#pragma once
//------------------------------------------------------------------------------
//  @file apple/pch.h
//	(C) 2015 See the LICENSE file.
//------------------------------------------------------------------------------
#ifdef __OBJC__
#import <Cocoa/Cocoa.h>
#import <Metal/Metal.h>
#import <MetalKit/MetalKit.h>
#import <QuartzCore/QuartzCore.h>
#import <AppKit/AppKit.h>

#define OBJC_ID_POINTER(T) id<T>
#define OBJC_POINTER(T) T*
#else
#define OBJC_ID_POINTER(T) void*
#define OBJC_POINTER(T) void*
#endif
