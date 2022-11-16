#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

sem_t chops[6];


void * philosopher(void* ind) {
    int i = *((int*)ind);
    while (1) {
        printf("Phil %d hungry \n", i);

        sem_wait(&chops[i]);
        sem_wait(&chops[(i+1)%5]);
        
        printf("Phil %d eating \n", i);
        sleep(2 + rand()%3);

        sem_post(&chops[(i+1)%5]);
        sem_post(&chops[i]);

        printf("Phil %d thinking \n", i);
        sleep(rand() % 4);
    }
}


int main() {
    srand(0);

    int philNums[] = {0, 1, 2, 3, 4};
    for (int i=0; i<5; i++)
        sem_init(&chops[i], 0, 1);

    pthread_t phils[5];

    for (int i=0; i<5; i++) {
        pthread_create(&phils[i], NULL, philosopher, &philNums[i]);
    }
    
    pthread_exit(NULL);
    return 0;
}