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
    struct sockaddr_in local_addr, multicast_addr;
    struct ip_mreq mreq;
    char buffer[MAX_BUFFER_SIZE];

    // Step 1: Create socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Step 2: Set SO_REUSEADDR option
    int reuse = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
        perror("Setting SO_REUSEADDR failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Step 3: Bind the socket
    memset(&local_addr, 0, sizeof(local_addr));
    local_addr.sin_family = AF_INET;
    local_addr.sin_addr.s_addr = INADDR_ANY;
    local_addr.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr*)&local_addr, sizeof(local_addr)) == -1) {
        perror("Binding failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Step 4: Set IP_ADD_MEMBERSHIP socket option
    mreq.imr_multiaddr.s_addr = inet_addr(MULTICAST_GROUP);
    mreq.imr_interface.s_addr = INADDR_ANY;
    if (setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0) {
        perror("Setting IP_ADD_MEMBERSHIP failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Step 5: Receive the datagram
    printf("Waiting for multicast messages...\n");
    socklen_t addr_len = sizeof(multicast_addr);
    recvfrom(sockfd, buffer, MAX_BUFFER_SIZE, 0, (struct sockaddr*)&multicast_addr, &addr_len);
    printf("Received message: %s", buffer);

    close(sockfd);

    return 0;
}
