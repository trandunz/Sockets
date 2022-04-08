#pragma once
#include "Global.h"
class Server
{
public:
	Server();
	~Server();

	void Init();
	void Update();

private:
	int m_ListenerSocket;
	int m_Status;
	char m_Buffer[BUFFER_SIZE]{};
};

