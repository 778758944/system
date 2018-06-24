#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <fcntl.h>
#include <errno.h>

#define oops(m) {perror(m); exit(1);}

void showdata(char *, int);

int main(int argc, char **argv) {
    struct timeval t;
    int fd1, fd2, maxfd;
    struct fd_set fds;
    int res;


    if ((fd1 = open(argv[1], O_RDONLY)) == -1) {
        oops("open err:");
    }

    if ((fd1 = open(argv[2], O_RDONLY)) == -1) {
        oops("open err:");
    }

    maxfd = 1 + (fd1 > fd2 ? fd1 : fd2);
    t.tv_sec = 5;
    t.tv_usec = 0;

    while(1) {
        FD_ZERO(&fds);
        FD_SET(fd1, &fds);
        FD_SET(fd1, &fds);
        res = select(maxfd, &fds, NULL, NULL, &t);

        if (res > 0) {
            if (FD_ISSET(fd1, &fds)) {
                showdata(argv[1], fd1);
            }

            if (FD_ISSET(fd2, &fds)) {
                showdata(argv[2], fd2);
            }
        } else {
            puts("no input");
        }

    }
}

void showdata(char * str, int fd) {
    char buf[BUFSIZ];
    read(fd, buf, BUFSIZ);
    printf("%s: %s\n", str, buf);
    fflush(stdout);
}