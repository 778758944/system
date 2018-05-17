#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/file.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

#define oops(m) {perror(m); exit(1);}

void lock_operation(int fd, int op);

int main(int argc, char **argv) {
    if (argc != 2) {
        oops("Usage:");
    }

    int fd;
    time_t now;
    char * message;

    if ((fd = open(argv[1], O_CREAT|O_TRUNC|O_WRONLY, 0644)) == -1) {
        oops("open:");
    }

    printf("fd = %d\n", fd);

    while (1) {
        time(&now);
        message = ctime(&now);
        lock_operation(fd, F_WRLCK);
        lseek(fd, 0, SEEK_SET);
        write(fd, message, strlen(message));
        lock_operation(fd, F_UNLCK);
        sleep(1);
    }
}

void lock_operation(int fd, int op) {
    struct flock lock;
    lock.l_start = lock.l_len = 0;
    lock.l_type = op;
    lock.l_pid = getpid();
    lock.l_whence = SEEK_SET;
    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        oops("lock:");
    }
}