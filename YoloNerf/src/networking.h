#ifndef HEADER_NETWORKING_H
#define HEADER_NETWORKING_H

//.///////////////////////////////////////////////////////////////////////////
//    SYSTEM IMPORTS FOR SOCKETS AND THREADS     /////////////////////////////
#include <pthread.h> // 'PThreads for Win32' lib is used on windows
#include <sys/types.h>

#ifdef _WIN32
#include <WinSock2.h>
#include <ws2tcpip.h>
#elif __APPLE__ || __linux__
#include <sys/socket.h>
#include <netinet/in.h>
#endif
#if __linux__
#include <arpa/inet.h>
#endif
//    SYSTEM IMPORTS FOR SOCKETS AND THREADS     /////////////////////////////
//.///////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#include "globals.h"

#ifdef _WIN32
#define PYTHON_CLIENT_PORT "1805"
#else
#define PYTHON_CLIENT_PORT 1805
#endif


namespace YoloNerf {
	class NetworkHandler {
#ifdef _WIN32
		WSADATA wsaData;
#endif

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