#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    WSADATA wsaData;
    SOCKET server_fd, new_socket;
    struct sockaddr_in address;
    char buffer[BUFFER_SIZE] = "Welcome to the Server!";
    int addrlen = sizeof(address);

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed\n");
        return 1;
    }

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        perror("Socket failed");
        WSACleanup();
        return 1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;  // Accept connections from any IP
    address.sin_port = htons(PORT);

    // Bind the socket
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) == SOCKET_ERROR) {
        perror("Bind failed");
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) == SOCKET_ERROR) {
        perror("Listen failed");
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    printf("Server listening on port %d\n", PORT);

    // Accept an incoming connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (int*)&addrlen)) == INVALID_SOCKET) {
        perror("Accept failed");
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    // Send a welcome message to the client
    send(new_socket, buffer, strlen(buffer), 0);
    printf("Welcome message sent to client\n");

    // Close the socket
    closesocket(new_socket);
    closesocket(server_fd);

    // Clean up Winsock
    WSACleanup();

    return 0;
}
