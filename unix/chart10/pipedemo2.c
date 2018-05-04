#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#define CHILE_MESS "I want a cookie\n"
#define PAR_MESS "testing...\n"
#define oops(m, x) {perror(m); exit(x);}
#define BUFFSIZE 100

int main() {
    int pipefd[2];
    int len;
    char buf[BUFFSIZE];
    int read_len;

    if (pipe(pipefd) == -1) {
        oops("error", 1);
    }

    switch(fork()) {
        case -1:
            oops("can not fork", 2);

        case 0:
            len = strlen(CHILE_MESS);
            while(1) {
                if (write(pipefd[1], CHILE_MESS, len) != len) {
                    oops("write error", 1);
                }
                sleep(5);
            }

        default:
            len = strlen(PAR_MESS);
            while(1) {
                if (write(pipefd[1], PAR_MESS, len) != len) {
                    oops("write error", 1);
                }

                sleep(1);

                read_len = read(pipefd[0], buf, BUFFSIZE);

                if (read_len < 0) {
                    break;
                }

                write(1, buf, read_len);
            }

    }
}