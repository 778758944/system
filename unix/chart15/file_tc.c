#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/file.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

#define oops(m) {perror(m); exit(1);}

void lock_operation(int, int);

int main(int argc, char **argv) {
    if (argc != 2) {
        oops("error:");
    }

    int fd, nread;
    char buf[BUFSIZ];
    if ((fd = open(argv[1], O_RDONLY)) == -1) {
        oops("create");
    }
    lock_operation(fd, F_RDLCK);
    nread = read(fd, buf, BUFSIZ);
    lock_operation(fd, F_UNLCK);
    printf("%s\n", buf);
    close(fd);
    return 0;
}

void lock_operation(int fd, int op) {
    struct flock lock;
    lock.l_len = lock.l_start = 0;
    lock.l_pid = getpid();
    lock.l_type = op;
    lock.l_whence = SEEK_SET;
    fcntl(fd, F_SETLKW, &lock);
}

