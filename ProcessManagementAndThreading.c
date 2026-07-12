#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *threadOne(void *arg) {
    printf("Thread 1 is checking system information...\n");
    sleep(1);
    printf("Thread 1 completed\n");

    pthread_exit(NULL);
}

void *threadTwo(void *arg) {
    printf("Thread 2 is checking memory...\n");
    sleep(1);
    printf("Thread 2 completed\n");

    pthread_exit(NULL);
}

void *threadThree(void *arg) {
    printf("Thread 3 is scheduling processes...\n");
    sleep(1);
    printf("Thread 3 completed\n");

    pthread_exit(NULL);
}

int main() {
    pthread_t thread1, thread2, thread3;

    pthread_create(&thread1, NULL, threadOne, NULL);
    pthread_create(&thread2, NULL, threadTwo, NULL);
    pthread_create(&thread3, NULL, threadThree, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    printf("All threads completed\n");

    return 0;
}
