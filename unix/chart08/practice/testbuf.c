#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
int main() {
    // line buffered
    printf("hello world\n");
    int pid = fork();
    if (pid == 0) {
        printf("I was forked\n");
        // exit(1);
    } else {
        wait(NULL);
        printf("forked\n");
    }
    sleep(5);
    return 0;
}