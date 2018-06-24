#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    int i;
    if (fork() != 0) {
        printf("main process\n");
        wait(NULL);
    }

    for(i = 0; i <= 10; i++) {
        printf("still here...");
        sleep(i);
    }

    return 0;
}