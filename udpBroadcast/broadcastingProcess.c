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
    // error handling

    struct sockaddr_in broadcast_addr;

    int broadcastEnable = 1;

    setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcastEnable, sizeof(broadcastEnable));

    broadcast_addr.sin_family = AF_INET;
    broadcast_addr.sin_port = htons(PORT);
    broadcast_addr.sin_addr.s_addr = INADDR_BROADCAST;

    while(1) {
        printf("Enter your message to broadcast: ");
        fgets(message, sizeof(message), stdin);

        // exit condition
        sendto(sockfd, message, strlen(message), 0, (struct sockaddr*)&broadcast_addr, sizeof(broadcast_addr));

        

    }


    close(sockfd);
}
