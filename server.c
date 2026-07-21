#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddress;
    char message[100];

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket,
         (struct sockaddr *)&serverAddress,
         sizeof(serverAddress));

    listen(serverSocket, 1);

    printf("Server is waiting for client...\n");

    clientSocket = accept(serverSocket, NULL, NULL);

    read(clientSocket, message, sizeof(message));

    printf("Data received: %s\n", message);

    if (strncmp(message, "MSG:", 4) == 0)
    {
        strcpy(message, "ACK:Message received");
    }
    else
    {
        strcpy(message, "ERROR:Invalid protocol");
    }

    send(clientSocket, message, strlen(message) + 1, 0);

    close(clientSocket);
    close(serverSocket);

    return 0;
}
