#include <stdio.h>

int main()
{
    int pageSize, framesCount, n;

    printf("Enter page size: ");
    scanf("%d", &pageSize);

    printf("Enter number of frames: ");
    scanf("%d", &framesCount);

    printf("Enter number of page references: ");
    scanf("%d", &n);

    int pages[n], frames[framesCount], lastUsed[framesCount];

    printf("Enter page references:\n");

    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("\nPage Size: %d bytes\n", pageSize);

    /* FIFO */

    for (int i = 0; i < framesCount; i++)
        frames[i] = -1;

    int index = 0, fifoHits = 0, fifoFaults = 0;

    printf("\nFIFO Page Replacement\n");

    for (int i = 0; i < n; i++)
    {
        int found = 0;

        for (int j = 0; j < framesCount; j++)
        {
            if (frames[j] == pages[i])
            {
                found = 1;
                break;
            }
        }

        if (found)
        {
            fifoHits++;
            printf("Page %d: Hit\n", pages[i]);
        }
        else
        {
            frames[index] = pages[i];
            index = (index + 1) % framesCount;
            fifoFaults++;

            printf("Page %d: Fault\n", pages[i]);
        }
    }

    printf("\nFIFO Hits: %d\n", fifoHits);
    printf("FIFO Faults: %d\n", fifoFaults);
    printf("Hit Ratio: %.2f\n", (float)fifoHits / n);
    printf("Miss Ratio: %.2f\n", (float)fifoFaults / n);

    /* LRU */

    for (int i = 0; i < framesCount; i++)
    {
        frames[i] = -1;
        lastUsed[i] = -1;
    }

    int lruHits = 0, lruFaults = 0;

    printf("\nLRU Page Replacement\n");

    for (int i = 0; i < n; i++)
    {
        int found = -1;

        for (int j = 0; j < framesCount; j++)
        {
            if (frames[j] == pages[i])
            {
                found = j;
                break;
            }
        }

        if (found != -1)
        {
            lruHits++;
            lastUsed[found] = i;

            printf("Page %d: Hit\n", pages[i]);
        }
        else
        {
            int replace = 0;

            for (int j = 0; j < framesCount; j++)
            {
                if (frames[j] == -1)
                {
                    replace = j;
                    break;
                }

                if (lastUsed[j] < lastUsed[replace])
                    replace = j;
            }

            frames[replace] = pages[i];
            lastUsed[replace] = i;
            lruFaults++;

            printf("Page %d: Fault\n", pages[i]);
        }
    }

    printf("\nLRU Hits: %d\n", lruHits);
    printf("LRU Faults: %d\n", lruFaults);
    printf("Hit Ratio: %.2f\n", (float)lruHits / n);
    printf("Miss Ratio: %.2f\n", (float)lruFaults / n);

    return 0;
}
