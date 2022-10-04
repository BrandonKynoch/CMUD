#include "networking.h"

using namespace YoloNerf;

NetworkHandler::NetworkHandler() {
#ifdef _WIN32
    // Initialize Winsock
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed: %d\n", iResult);
        return;
    }
#endif

    pthread_t t;
    pthread_create(&t, NULL, &StaticAwaitConnections, this);
}

void NetworkHandler::AwaitConnections() {
#ifdef __linux__
    // Create the server socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PYTHON_CLIENT_PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // bind the socket to our specified IP and port
    bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));

    listen(server_socket, 1);

    // Wait for client to connect
    while (TRUE) {
        // Second parameter can tell us where the client connection is coming from
        int client_socket = accept(server_socket, NULL, NULL);

        //pthread_create(&threads[threads_index - 1], NULL, listen_to_drone, new_drone);

        // Send connection response
        //send(new_drone->socket, network_message, sizeof(network_message), 0); // last param is optional flags
    
        printf("\n\nClient Connected!\n\n");
    }
#endif
}