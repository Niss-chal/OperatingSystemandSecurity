#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int completedTasks = 0;

pthread_mutex_t lock;
sem_t semaphore;

void *threadOne(void *arg)
{
    printf("Thread 1 is checking system information\n");
    sleep(1);

    pthread_mutex_lock(&lock);
    completedTasks++;
    pthread_mutex_unlock(&lock);

    printf("Thread 1 completed\n");

    sem_post(&semaphore);

    return NULL;
}

void *threadTwo(void *arg)
{
    printf("Thread 2 is checking memory\n");
    sleep(1);

    pthread_mutex_lock(&lock);
    completedTasks++;
    pthread_mutex_unlock(&lock);

    printf("Thread 2 completed\n");

    sem_post(&semaphore);

    return NULL;
}

void *threadThree(void *arg)
{
    sem_wait(&semaphore);
    sem_wait(&semaphore);

    int burstTime[4] = {7,9,5,2};
    int remainingTime[4] = {7,9,5,2};
    int quantum = 3;
    int completed = 0;

    printf("\nThread 3 is starting round-robin scheduling\n");

    while (completed < 4)
    {
        for (int i = 0; i < 4; i++)
        {
            if (remainingTime[i] > 0)
            {
                printf("Process P%d is running\n", i + 1);

                if (remainingTime[i] > quantum)
                {
                    remainingTime[i] = remainingTime[i] - quantum;
                    printf("P%d remaining time: %d\n",
                           i + 1, remainingTime[i]);
                }
                else
                {
                    remainingTime[i] = 0;
                    printf("P%d completed\n", i + 1);
                    completed++;
                }

                sleep(1);
            }
        }
    }

    printf("Thread 3 completed scheduling\n");

    return NULL;
}

int main()
{
    pthread_t thread1, thread2, thread3;

    pthread_mutex_init(&lock, NULL);
    sem_init(&semaphore, 0, 0);

    pthread_create(&thread1, NULL, threadOne, NULL);
    pthread_create(&thread2, NULL, threadTwo, NULL);
    pthread_create(&thread3, NULL, threadThree, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    printf("\nCompleted tasks: %d\n", completedTasks);
    printf("All threads completed\n");

    pthread_mutex_destroy(&lock);
    sem_destroy(&semaphore);

    return 0;
}
