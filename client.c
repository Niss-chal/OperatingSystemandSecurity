#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int clientSocket;
    struct sockaddr_in serverAddress;
    char message[100];
    char username[30];
    char password[30];
    char login[100];

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (clientSocket < 0)
    {
        printf("Socket creation failed\n");
        return 1;
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(clientSocket,
                (struct sockaddr *)&serverAddress,
                sizeof(serverAddress)) < 0)
    {
        printf("Connection failed\n");
        close(clientSocket);
        return 1;
    }

    printf("Enter username: ");
    scanf("%30s", username);

    printf("Enter password: ");
    scanf("%30s", password);

    sprintf(login, "%s:%s", username, password);

    if (send(clientSocket, login, strlen(login) + 1, 0) < 0)
    {
        printf("Login details could not be sent\n");
        close(clientSocket);
        return 1;
    }

    if (read(clientSocket, message, sizeof(message)) <= 0)
    {
        printf("Authentication response not received\n");
        close(clientSocket);
        return 1;
    }

    if (strcmp(message, "AUTH_SUCCESS") != 0)
    {
        printf("Authentication failed\n");
        close(clientSocket);
        return 1;
    }

    printf("Authentication successful\n");

    strcpy(message, "MSG:Hello from client side!!!");

    if (send(clientSocket, message, strlen(message) + 1, 0) < 0)
    {
        printf("Message could not be sent\n");
        close(clientSocket);
        return 1;
    }

    if (read(clientSocket, message, sizeof(message)) <= 0)
    {
        printf("Server response not received\n");
        close(clientSocket);
        return 1;
    }

    printf("Server response: %s\n", message);

    close(clientSocket);

    return 0;
}
