#include <stdio.h>
#include <signal.h>
#include <stdlib.h>


int main(int argc, char **argv) {
    if (argc < 2) {
        exit(1);
    }
    int pid;
    sscanf(argv[1], "%d", &pid);
    printf("pid = %d\n", pid);
    kill(pid, SIGINT);
    return 0;
}