#include "Server.h"
#include "Client.h"
void main()
{
	Server server;
	//Client client;
	
	while (true)
	{
		server.Update();
		//client.Update();
	}
}
