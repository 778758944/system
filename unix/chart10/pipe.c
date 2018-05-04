#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#define oops(m,x) {perror(m); exit(x);}

int main(int argc, char **argv) {
    int pipefd[2];
    int pid;
    if (argc != 3) {
        oops("Usage error", 1);
    }

    if (pipe(pipefd) == -1) {
        oops("can not create pipe", 1);
    }

    pid = fork();

    if (pid > 0) {
        close(pipefd[1]);
        if (dup2(pipefd[0], 0) == -1) {
            oops("error to redirect", 1);
        }

        close(pipefd[0]);
        execlp(argv[2], argv[2], NULL);

        oops(argv[2], 1);

    }


    close(pipefd[0]);

    if (dup2(pipefd[1], 1) == -1) {
        oops("can not redirect", 1);
    }

    close(pipefd[1]);

    execlp(argv[1], argv[1], NULL);
    oops(argv[1], 2);
}