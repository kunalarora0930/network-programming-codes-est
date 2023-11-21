#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define PORT 6969
#define MAX_MESSAGE_LEN 1024

int main(){

    char message[MAX_MESSAGE_LEN];

    int sockfd;
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in recv_addr;

    recv_addr.sin_family = AF_INET;
    recv_addr.sin_port = htons(PORT);
    recv_addr.sin_addr.s_addr = INADDR_ANY;


    bind(sockfd, (struct sockaddr*)&recv_addr, sizeof(recv_addr));

    while(1) {
        int bytes_recvd = recvfrom(sockfd, message, sizeof(message), 0, (struct sockaddr*)&recv_addr, sizeof(recv_addr));

        // print message


    }

    close(sockfd);
    
}