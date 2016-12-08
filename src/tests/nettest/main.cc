//------------------------------------------------------------------------------
/**
    @file nettest/main.cc
    
	Main entry point for the net test
	
	(C) 2015 See the LICENSE file.
*/
#include "config.h"
#include "application.h"
#include "sysfunc.h"
#include "win32/win32socket.h"
#include "appargs.h"

JARVIS_MAIN
{
	Core::SysFunc sysfunc;
	Core::AppArgs args;
	args.Set(argv, argc);
	if (args.Flag("-server"))
	{
		Win32::Socket sock;
		sock.Listen("81");

		
		while (true)
		{
			Win32::Socket sock2 = sock.Accept();
			printf("Client connected!\n");

			while (!sock2.PendingData());

			char buf[1024];
			SizeT size = sock2.Receive(buf, 1024);
			String str(buf, size);
			printf("Got message %s\n", str.CharPtr());
		}		
	}
	else
	{
		Win32::Socket sock;
		sock.Connect(args.Value("-address"), args.Value("-port"));
		String html("<html><body>Hej!</body></html>");
		sock.Send(html.CharPtr(), html.Length());
		while (true);
	}
	
	return 0;
}
