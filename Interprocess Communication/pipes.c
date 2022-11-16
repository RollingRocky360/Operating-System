#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2];

    if (pipe(fd) == -1) {
        printf("Couldn't plumb \n");
        return 1;
    };

    if (fork() == 0) {
        close(fd[0]);
        dup2(fd[1], 1);
        close(fd[1]);
        execlp("ls", "ls", NULL);
    } else {
        close (fd[1]);
        dup2(fd[0], 0);
        close(fd[0]);
        execlp("wc", "wc", "-l", NULL);
    }

    return 0;
}