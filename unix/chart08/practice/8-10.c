#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

void handle();
void child_process();
static int j;
static int max;
int main(int argc, char **argv) {
    signal(SIGCHLD, handle);
    if(argc < 2) {
        exit(1);
    }
    sscanf(argv[1], "%d", &max);

    for(int i = 0; i < max; i++) {
        if (fork() == 0) {
            child_process();
        } else {

        }
    }

    while (1) {
        puts("loop");
        sleep(1);
    }
    return 0;
}

void handle() {
    if (j < max) {
        int pid = wait(NULL);
        printf("process %d\n", pid);
        j++;
    }
}

void child_process() {
    sleep(5);
    exit(1);
}

