#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int clientSocket;
    struct sockaddr_in serverAddress;
    char message[100];

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(clientSocket,
            (struct sockaddr *)&serverAddress,
            sizeof(serverAddress));

    strcpy(message, "MSG:Hello from client side!!");

    send(clientSocket, message, strlen(message) + 1, 0);

    read(clientSocket, message, sizeof(message));

    printf("Server response: %s\n", message);

    close(clientSocket);

    return 0;
}
