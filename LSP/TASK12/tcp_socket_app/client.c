#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    WSADATA wsaData;
    SOCKET sock;
    struct sockaddr_in server_address;
    char buffer[BUFFER_SIZE] = {0};

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed\n");
        return -1;
    }

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        perror("Socket creation failed");
        WSACleanup();
        return -1;
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);

    // Use inet_addr instead of inet_pton
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (server_address.sin_addr.s_addr == INADDR_NONE) {
        perror("Invalid address");
        closesocket(sock);
        WSACleanup();
        return -1;
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&server_address, sizeof(server_address)) == SOCKET_ERROR) {
        perror("Connection failed");
        closesocket(sock);
        WSACleanup();
        return -1;
    }

    // Receive the welcome message from the server
    recv(sock, buffer, sizeof(buffer), 0);
    printf("Received from server: %s\n", buffer);

    // Close the socket
    closesocket(sock);

    // Clean up Winsock
    WSACleanup();

    return 0;
}
