#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>

#define oops(m) {perror(m); exit(1);}

void showdata(char * name, int fd);

int main(int argc, char **argv) {
    int fd1, fd2;
    struct timeval timeout;
    fd_set readfds;
    int maxfd;
    int retval;

    if (argc != 4) {
        oops("Usage:");
    }

    if ((fd1 = open(argv[1], O_RDONLY)) == -1) {
        oops(argv[1]);
    }

    if ((fd2 = open(argv[2], O_RDONLY)) == -1) {
        oops(argv[2]);
    }

    maxfd = 1 + (fd1 > fd2 ? fd1 : fd2);

    while(1) {
        FD_ZERO(&readfds);
        FD_SET(fd1, &readfds);
        FD_SET(fd2, &readfds);

        timeout.tv_sec = atoi(argv[3]);
        timeout.tv_usec = 0;

        retval = select(maxfd, &readfds, NULL, NULL, &timeout);

        if (retval == -1) {
            oops("select");
        }

        if (retval > 0) {
            if (FD_ISSET(fd1, &readfds)) {
                showdata(argv[1], fd1);
            }
            if (FD_ISSET(fd2, &readfds)) {
                showdata(argv[2], fd2);
            }
        } else {
            printf("no input");
        }

    }
}

void showdata(char * name, int fd) {
    char buf[BUFSIZ];
    int n;

    printf("%s:", name);
    fflush(stdout);
    n = read(fd, buf, BUFSIZ);
    if (n == -1) {
        oops(name);
    }

    write(1, buf, n);
    write(1, "\n", 1);
}