#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define PORT 6969
#define SERVER_IP "127.0.0.1"
#define BUFFER_SIZE 1024

int main() {
    char buffer[BUFFER_SIZE];

    int client_socket;
    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);



    while(1) {
        connect(client_socket, (struct sockaddr*) &server_addr, sizeof(server_addr));
        printf("Connected\n");
        printf("Client(You): ");
        fgets(buffer, sizeof(buffer), stdin);

        size_t bytes_sent = send(client_socket, buffer, strlen(buffer), 0);

        if(strcmp(buffer, "exit\n") == 0) {
            printf("Exiting ...\n");
            break;
        }

        size_t bytes_recvd = recv(client_socket, buffer, sizeof(buffer), 0);
        buffer[bytes_recvd] = '\0';
        printf("Server: %s\n", buffer);


    }
    close(client_socket);
}