#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *file;
    int choice;
    char text[200];

    printf("1. Create and write file\n");
    printf("2. Read file\n");
    printf("3. Delete file\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar();

    if (choice == 1)
    {
        file = fopen("myfile.txt", "w");

        if (file == NULL)
        {
            printf("File could not be created\n");
            return 1;
        }

        printf("Enter text: ");
        fgets(text, sizeof(text), stdin);

        fprintf(file, "%s", text);
        fclose(file);

        printf("File created and written successfully\n");
    }
    else if (choice == 2)
    {
        file = fopen("myfile.txt", "r");

        if (file == NULL)
        {
            printf("File does not exist\n");
            return 1;
        }

        printf("File content:\n");

        while (fgets(text, sizeof(text), file) != NULL)
        {
            printf("%s", text);
        }

        fclose(file);
    }
    else if (choice == 3)
    {
        if (remove("myfile.txt") == 0)
        {
            printf("File deleted successfully\n");
        }
        else
        {
            printf("File could not be deleted\n");
        }
    }
    else
    {
        printf("Invalid choice\n");
    }

    return 0;
}
