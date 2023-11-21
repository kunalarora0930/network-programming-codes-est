#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 6969
#define SERVER_IP "127.0.0.1"
#define BUFFER_SIZE 1024

int main(){
    char buffer[BUFFER_SIZE];

    int client_socket;

    struct sockaddr_in server_addr;

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    while(1) {
        printf("Client(You): ");
        fgets(buffer, sizeof(buffer), stdin);

        // Add condition for exit
        int bytes_sent = sendto(client_socket, buffer, sizeof(buffer), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));


        int bytes_recvd = recvfrom(client_socket, buffer, sizeof(buffer), 0, (struct sockaddr*)& server_addr, sizeof(server_addr));

        buffer[bytes_recvd] = '\0';

        printf("%s", buffer);

    }

    close(client_socket);
}