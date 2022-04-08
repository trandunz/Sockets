#include "Server.h"

Server::Server()
{
	Init();
}

Server::~Server()
{
	closesocket(m_ListenerSocket);
}

void Server::Init()
{
	InitWSA();

	int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

	if (serverSocket == -1)
	{
		printf("Error: Socket() failed. Code: %d\n", WSAGetLastError());
		exit(-1);
	}

	struct sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(7000);
	serverAddr.sin_addr.s_addr = INADDR_ANY;

	m_Status = bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(struct sockaddr));
	if (m_Status == 1)
	{
		printf("Error: Bind() failed. Code: %d\n", WSAGetLastError());
		exit(-1);
	}

	printf("Listening...\n");
	m_Status = listen(serverSocket, 5);
	if (m_Status == -1)
	{
		printf("Error: Listen() failed. Code: %d\n", WSAGetLastError());
		exit(-1);
	}

	struct sockaddr_in senderAddr;
	int length = sizeof(senderAddr);
	m_ListenerSocket = accept(serverSocket, (struct sockaddr*)&senderAddr, &length);
	if (m_ListenerSocket == -1)
	{
		printf("Error: Accept() failed. Code: %d\n", WSAGetLastError());
		printf("Accepting next connection...\n\n");
	}
	printf("A Connection from %s has been accepted\n", inet_ntoa(senderAddr.sin_addr));
}

void Server::Update()
{
	printf("Waiting for a message...\n");
	m_Status = recv(m_ListenerSocket, m_Buffer, BUFFER_SIZE, 0);
	if (m_Status == -1)
	{
		printf("Error: recv() failed. Code: %d\n", WSAGetLastError());
		exit(-1);
		return;
	}
	m_Buffer[m_Status] = '\0';
	printf("The message recieved is: ");
	printf("%s\n\n", m_Buffer);
}
