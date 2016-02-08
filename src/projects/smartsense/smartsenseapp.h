#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::SmartSense::SmartSenseApp
	
    Main application for the smart sense region project
	
	(C) 2015 See the LICENSE file.
*/
//------------------------------------------------------------------------------
#include "application.h"
#include "imagestream.h"
#include "recognizer.h"
namespace JARVIS {
namespace SmartSense
{
class SmartSenseApp : public Core::Application
{
public:
    /// constructor
    SmartSenseApp();
    /// destructor
    virtual ~SmartSenseApp();
    
    /// setup the application context
    virtual void OnSetup();
    /// run the application code
    virtual void OnFrame();
    /// exit function
    virtual void OnExit();
    
private:
    uint32 frameCounter;
    Ptr<ImageStream> stream;
    Ptr<Recognizer> detector;
    Ptr<Recognizer> tracker;
};

}} // namespace JARVIS::SmartSense