#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    WSADATA wsaData;
    SOCKET sockfd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[BUFFER_SIZE];
    int len = sizeof(client_addr);

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed\n");
        return 1;
    }

    // Create a socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
        perror("Socket creation failed");
        WSACleanup();
        return 1;
    }

    // Set up the server address struct
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind the socket to the port
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        perror("Bind failed");
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    printf("Server listening on port %d\n", PORT);

    // Receive a message from the client
    int n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &len);
    buffer[n] = '\0';  // Null-terminate the received string
    printf("Received message: %s\n", buffer);

    // Send a response back to the client
    const char *response = "Hello from Server";
    sendto(sockfd, response, strlen(response), 0, (struct sockaddr *)&client_addr, len);
    printf("Response sent to client: %s\n", response);

    // Close the socket
    closesocket(sockfd);
    WSACleanup();
    return 0;
}
