#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_BUFFER_SIZE 1024
#define MULTICAST_GROUP "239.0.0.1"
#define PORT 12345

int main() {
    int sockfd;
    struct sockaddr_in multicast_addr;
    char buffer[MAX_BUFFER_SIZE];

    // Step 1: Create socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Step 2: Initialize sockaddr_in structure
    memset(&multicast_addr, 0, sizeof(multicast_addr));
    multicast_addr.sin_family = AF_INET;
    multicast_addr.sin_addr.s_addr = inet_addr(MULTICAST_GROUP);
    multicast_addr.sin_port = htons(PORT);

    // Step 3: Set IP_MULTICAST_LOOP socket option
    int loop = 1;
    if (setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_LOOP, &loop, sizeof(loop)) < 0) {
        perror("Setting IP_MULTICAST_LOOP failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Step 4: Set IP_MULTICAST_IF socket option
    struct in_addr localInterface;
    localInterface.s_addr = INADDR_ANY;
    if (setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_IF, &localInterface, sizeof(localInterface)) < 0) {
        perror("Setting IP_MULTICAST_IF failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Step 5: Send the datagram
    printf("Enter message to multicast: ");
    fgets(buffer, MAX_BUFFER_SIZE, stdin);
    sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr*)&multicast_addr, sizeof(multicast_addr));

    close(sockfd);

    return 0;
}
