//------------------------------------------------------------------------------
/**
    @file nettest/main.cc
    
	Main entry point for the net test
	
	(C) 2015 See the LICENSE file.
*/
#include "config.h"
#include "application.h"
#include "sysfunc.h"
#include "network/socket.h"
#include "appargs.h"

JARVIS_MAIN
{
	Core::SysFunc sysfunc;
	Core::AppArgs args;
	args.Set(argv, argc);
	if (args.Flag("-server"))
	{
		Ptr<Network::Socket> sock = Network::Socket::Create();
		sock->Listen("81");

		
		while (true)
		{
			Ptr<Network::Socket> sock2 = sock->Accept();
			printf("Client connected!\n");

			char buf[1024];
			SizeT size = sock2->Receive(buf, 1024);
			String str(buf, size);
			//printf("Got message %s\n", str.CharPtr());
			String response("<html><body>Hej!</body></html>");
			sock2->Send(response.CharPtr(), response.Length());
		}		
	}
	else
	{
		Ptr<Network::Socket> sock = Network::Socket::Create();
		sock->Connect(args.Value("-address"), args.Value("-port"));
		String html("<html><body>Hej!</body></html>");
		sock->Send(html.CharPtr(), html.Length());
	}
	
	return 0;
}
