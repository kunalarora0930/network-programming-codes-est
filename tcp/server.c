#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 6969
#define BUFFER_SIZE 1024

int main() {

    char buffer[BUFFER_SIZE];

    // create socket
    int client_socket, server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(server_socket == -1) {
        printf("Socket creation failed :(");
        exit(EXIT_FAILURE);
    }

    // create socket address
    struct sockaddr_in server_addr, client_addr;
    // memset(server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // bind
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        printf("Error in binding socket :(");
        exit(EXIT_FAILURE);
    }

    // listen
    if (listen(server_socket, 5) == -1){
        printf("Eroor :(");
    }
    printf("Listening on port %d\n", PORT);

    socklen_t addr_size = sizeof(client_addr);

    while(1) {
        client_socket = accept(server_socket, (struct sockaddr*) & client_addr, &addr_size);
        if(client_socket == -1) {
            printf("Eroor :(");
            exit(EXIT_FAILURE);
        }
        printf("Connection Accepted\n");

        size_t bytes_recvd = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes_recvd < 0) {
            printf("Eroor :(");
            exit(EXIT_FAILURE);
        }
        buffer[bytes_recvd] = '\0';
        printf("Client: %s", buffer);

        if(strcmp(buffer, "exit\n") == 0) {
            close(client_socket);
            break;
        }
        size_t bytes_sent = send(client_socket, buffer, bytes_recvd, 0);


    }
    close(server_socket);
}