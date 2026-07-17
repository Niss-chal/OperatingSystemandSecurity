#include <stdio.h>

int main()
{
    int pageSize;
    int frameCount;
    int referenceCount;

    printf("Enter page size: ");
    scanf("%d", &pageSize);

    printf("Enter number of frames: ");
    scanf("%d", &frameCount);

    printf("Enter number of page references: ");
    scanf("%d", &referenceCount);

    int pages[referenceCount];
    int frames[frameCount];

    printf("Enter page references:\n");

    for (int i = 0; i < referenceCount; i++)
    {
        scanf("%d", &pages[i]);
    }

    for (int i = 0; i < frameCount; i++)
    {
        frames[i] = -1;
    }

    int index = 0;
    int hits = 0;
    int faults = 0;

    printf("\nPage Size: %d bytes\n", pageSize);
    printf("\nFIFO Page Replacement\n");

    for (int i = 0; i < referenceCount; i++)
    {
        int found = 0;

        for (int j = 0; j < frameCount; j++)
        {
            if (frames[j] == pages[i])
            {
                found = 1;
                break;
            }
        }

        if (found == 1)
        {
            hits++;
            printf("Page %d: Hit\n", pages[i]);
        }
        else
        {
            frames[index] = pages[i];
            index = (index + 1) % frameCount;

            faults++;
            printf("Page %d: Fault\n", pages[i]);
        }
    }

    printf("\nPage Hits: %d\n", hits);
    printf("Page Faults: %d\n", faults);

    return 0;
}
