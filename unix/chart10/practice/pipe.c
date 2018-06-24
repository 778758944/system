#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#define oops(m) {perror(m); exit(1);}

int main(int argc, char **argv) {
    int i, pid;
    int fd[2];

    if (argc < 2) {
        oops("Usage:");
    }

    if (pipe(fd) == -1) {
        oops("pipe error:");
    }



    

    for (i = 1; i < argc-1; i++) {
        int pid = fork();
        if (pid > 0) {

        } else {
            if (i == 1) {
                close(fd[0]);
                if (dup2(fd[1], 1) == -1) {
                    oops("dup2 error:");
                }
                close(fd[1]);
            } else {
                if (dup2(fd[0], 0) == -1 || dup2(fd[1], 1) == -1) {
                    oops("dup2: ");
                }
                close(fd[0]);
                close(fd[1]);
            }

            execlp(argv[i], argv[i], NULL);
            oops("exe error:");

        }
    }
    close(fd[1]);
    if (dup2(fd[0], 0) == -1) {
        oops("dup2:");
    }
    execlp(argv[i], argv[i], NULL);
    oops("exe error:");
}