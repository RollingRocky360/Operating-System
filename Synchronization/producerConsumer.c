#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

int BUFFER[5];
int START=0; int END=0;
sem_t mutex;
sem_t empty;
sem_t full;


void* producer() {
    int i = 0;
    while (i++ < 10) {

        sem_wait(&empty);
        sem_wait(&mutex);

        // int i = rand() % 10;
        BUFFER[(END %= 5)] = i; END++;
        sleep(rand()%5);
        printf("Produced %d\n", i);

        sem_post(&mutex);
        sem_post(&full);
    }
}

void* consumer() {
    while (1) {
        sem_wait(&full);
        sem_wait(&mutex);

        int i = BUFFER[(START %= 5)]; START++;
        printf("Consumed %d\n", i);

        sem_post(&mutex);
        sem_post(&empty);
    }
}

int main() {

    srand(time(NULL));

    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, 5);
    sem_init(&full, 0, 0);

    pthread_t cons, prod;
    pthread_create(&cons, NULL, consumer, NULL);
    pthread_create(&prod, NULL, producer, NULL);

    pthread_exit(NULL);

    return 0;
}