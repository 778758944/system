#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#define BUFFSIZE 100

int main() {
    int len, i, apipe[2];
    char buf[BUFFSIZE];
    /* get a pipe */
    if (pipe(apipe) == -1) {
        perror("make pipe error");
        exit(1);
    }

    printf("Got a pipe! It is file {%d %d}", apipe[0], apipe[1]);
    while(fgets(buf, BUFFSIZE, stdin)) {
        len = strlen(buf);

        if (write(apipe[1], buf, len) != len) {
            perror("can write pipe");
            break;
        }

        // reset buf to XXXXXX

        for(i = 0; i < len; i++) {
            buf[i] = 'X';
        }

        // reset buf form pipe;

        len = read(apipe[0], buf, BUFFSIZE);

        if (len == -1) {
            perror("error in read pipe");
            break;
        }

        if (write(1, buf, len) != len) {
            perror("waiting to stdout");
            break;
        }
    }
}