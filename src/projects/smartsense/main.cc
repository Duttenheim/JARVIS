//------------------------------------------------------------------------------
//  @file smartsense/main.cc
//	(C) 2016 See the LICENSE file.
//------------------------------------------------------------------------------
#include "config.h"
#include "smartsenseapp.h"

JARVIS_MAIN
{
    SmartSense::SmartSenseApp app;
    app.SetAppArgs(argv, argc);
    app.Start();
}
