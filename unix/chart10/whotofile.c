#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>

int main() {
    int pid;
    int fd;

    if ((pid = fork()) == -1) {
        perror("error to open file");
        exit(1);
    }

    if (pid == 0) {
        close(1);
        fd = open("userlist", O_RDWR);
        execlp("who", "who", NULL);
        perror("error to execute");
        exit(1);
    }

    if (pid != 0) {
        wait(NULL);
        printf("Done\n");
    }
}