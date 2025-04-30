#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    WSADATA wsaData;
    SOCKET sockfd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

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
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Send a message to the server
    const char *message = "Hello from Client";
    sendto(sockfd, message, strlen(message), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
    printf("Message sent to server: %s\n", message);

    // Receive a response from the server
    int n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, NULL, NULL);
    buffer[n] = '\0';  // Null-terminate the received string
    printf("Received from server: %s\n", buffer);

    // Close the socket
    closesocket(sockfd);
    WSACleanup();
    return 0;
}
