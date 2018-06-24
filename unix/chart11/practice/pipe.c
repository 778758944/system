#include <stdio.h>
#include <unistd.h>
#include <time.h>
int main() {
    int fd[2];
    time_t t;

    pipe(fd);
    if (!!t) {
        puts("true");
    } else {
        puts("false");
    }

    return 0;
}