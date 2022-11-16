#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/fcntl.h>
#include <unistd.h>

int main() {
    
    if (fork() > 0) {
        key_t key = 5800;

        int shmid = shmget(key, 128, 0666 | IPC_CREAT);
        char* mem = shmat(shmid, NULL, 0);

        char msg[] = "Hello there";
        char* s = mem;

        for (int i=0; i<strlen(msg); i++)
            *s++ = msg[i];
        
        printf("Parent: Message sent \n");
        while (*mem != '*') sleep(1);

    } else {
        key_t key = 5800;

        int shmid = shmget(key, 128, 0666);
        char* mem = shmat(shmid, NULL, 0);

        char buff[100];
        strcpy(buff, mem);

        printf("Child: Message Received - %s \n", buff);
        *mem = '*';
    }

    return 0;
}
