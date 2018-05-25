#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#define oops(m) {perror(m); exit(1);}


int main(int argc, char ** argv) {
    if (argc < 2) {
        oops("Usage: ");
    }
    int pd[2], pid;
    if (pipe(pd) == -1) {
        oops("pipe error:");
    }

    pid = fork();

    if (pid > 0) {
        close(pd[1]);
        if (dup2(pd[0], 0) == -1) {
            oops("dup2:");
        }
        close(pd[0]);
        puts("main process");
        execlp("sort", "sort", NULL);
        oops("error:");
    } else {
        close(pd[0]);
        if (dup2(pd[1], 1) == -1) {
            oops("dup2:");
        }
        puts("child process");
        close(pd[1]);
        execlp("cat", "cat", argv[1], NULL);
        oops("error:");
    }

    return 0;

    


}