#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>

void *handleClient(void *arg)
{
    int clientSocket = *(int *)arg;
    char login[100];
    char message[100];

    free(arg);

    if (read(clientSocket, login, sizeof(login)) <= 0)
      {
        printf("Login details could not be received\n");
        close(clientSocket);
        return NULL;
      }

    if (strcmp(login, "admin:linux") != 0)
      {
        strcpy(message, "AUTH_FAILED");
        send(clientSocket, message, strlen(message) + 1, 0);

        printf("Client authentication failed\n");
        close(clientSocket);
        return NULL;
      }
    strcpy(message, "AUTH_SUCCESS");

    if (send(clientSocket, message, strlen(message) + 1, 0) < 0)
    {
        printf("Authentication response failed\n");
        close(clientSocket);
        return NULL;
    }

    if (read(clientSocket, message, sizeof(message)) <= 0)
    {
        printf("Message could not be received\n");
        close(clientSocket);
        return NULL;
    }

    printf("Data received: %s\n", message);

    if (strncmp(message, "MSG:", 4) == 0 &&
        strlen(message) > 4)
    {
        strcpy(message, "ACK:Message received from server side!!!");
    }
    else
    {
        strcpy(message, "ERROR:Invalid message");
    }

    if (send(clientSocket, message, strlen(message) + 1, 0) < 0)
    {
        printf("Response could not be sent\n");
    }

    close(clientSocket);
    return NULL;
}

int main()
{
    int serverSocket;
    struct sockaddr_in serverAddress;

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket < 0)
    {
        printf("Socket creation failed\n");
        return 1;
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket,
             (struct sockaddr *)&serverAddress,
             sizeof(serverAddress)) < 0)
    {
        printf("Bind failed\n");
        close(serverSocket);
        return 1;
    }

    if (listen(serverSocket, 5) < 0)
    {
        printf("Listen failed\n");
        close(serverSocket);
        return 1;
    }

    printf("Server is waiting for clients...\n");

    while (1)
    {
        int *clientSocket = malloc(sizeof(int));

        *clientSocket = accept(serverSocket, NULL, NULL);

        if (*clientSocket < 0)
        {
            printf("Client connection failed\n");
            free(clientSocket);
            continue;
        }

        pthread_t thread;

        if (pthread_create(&thread, NULL,
                           handleClient, clientSocket) != 0)
        {
            printf("Thread creation failed\n");
            close(*clientSocket);
            free(clientSocket);
            continue;
        }

        pthread_detach(thread);
    }

    close(serverSocket);
    return 0;
}
