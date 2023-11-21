#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 6969
#define BUFFER_SIZE 1024

int main() {
    char buffer[BUFFER_SIZE];
    int server_socket, client_socket;

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr, client_addr;

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = ntohs(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_socket, (struct sockaddr*)& server_addr, sizeof(server_addr));

    socklen_t client_addr_len = sizeof(client_addr);

    while(1) {
        int bytes_recvd = recvfrom(server_socket, buffer, sizeof(buffer), 0, (struct sockaddr*)&client_socket, &client_addr_len);
        buffer[bytes_recvd] = '\0';


        if(strcmp(buffer, "exit\n") == 0) {
            close(server_socket)
            break;
        }
        printf("Client: %s\n", buffer);

        sendto(server_socket, buffer, sizeof(buffer), 0, (struc sockaddr*)&client_addr, client_addr_len);

        close(client_socket);
    }
    close(server_socket);

}