#ifndef HEADER_NETWORKING_H
#define HEADER_NETWORKING_H

#include <stdio.h>
#include <stdlib.h>

#include <pthread.h> // 'PThreads for Win32' lib is used on windows

#include <sys/types.h>

#ifdef _WIN32
#include <WinSock2.h>
#include <ws2tcpip.h>

#elif __APPLE__ || __linux__
#include <sys/socket.h>
#include <netinet/in.h>
#endif



#define PYTHON_CLIENT_PORT 1805

namespace YoloNerf {
	class NetworkHandler {
		WSADATA wsaData;

	public:
		NetworkHandler();
		void AwaitConnections();
	};

	static void* StaticAwaitConnections(void* instance) {
		((NetworkHandler*)instance)->AwaitConnections();
		return NULL;
	}
}

#endif