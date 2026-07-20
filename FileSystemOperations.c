#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int main()
{
    FILE *file;
    int choice, permission;
    char filename[50];
    char text[200];
    char username[20];
    char password[20];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    if (strcmp(username, "admin") != 0 ||
        strcmp(password, "linux") != 0)
    {
        printf("Authentication failed\n");
        return 1;
    }

    printf("Login successful\n\n");

    printf("1. Create file\n");
    printf("2. Write file\n");
    printf("3. Read file\n");
    printf("4. Delete file\n");
    printf("5. Set file permission\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    printf("Enter file name: ");
    scanf("%s", filename);
    getchar();

    if (choice == 1)
    {
        file = fopen(filename, "w");

        if (file == NULL)
        {
            printf("File could not be created\n");
            return 1;
        }

        fclose(file);
        printf("File created successfully\n");
    }
    else if (choice == 2)
    {
        file = fopen(filename, "w");

        if (file == NULL)
        {
            printf("File could not be opened\n");
            return 1;
        }

        printf("Enter text: ");
        fgets(text, sizeof(text), stdin);

        fprintf(file, "%s", text);
        fclose(file);

        printf("File written successfully\n");
    }
    else if (choice == 3)
    {
        file = fopen(filename, "r");

        if (file == NULL)
        {
            printf("File does not exist or permission denied\n");
            return 1;
        }

        printf("File content:\n");

        while (fgets(text, sizeof(text), file) != NULL)
        {
            printf("%s", text);
        }

        fclose(file);
    }
    else if (choice == 4)
    {
        if (remove(filename) == 0)
        {
            printf("File deleted successfully\n");
        }
        else
        {
            printf("File could not be deleted\n");
        }
    }
    else if (choice == 5)
    {
        printf("Enter permission such as 755 or 644: ");
        scanf("%o", &permission);

        if (chmod(filename, permission) == 0)
        {
            printf("File permission changed successfully\n");
        }
        else
        {
            printf("File does not exist\n");
        }
    }
    else
    {
        printf("Invalid choice\n");
    }

    return 0;
}
