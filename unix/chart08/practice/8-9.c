#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
void handle();
int main(int argc, char ** argv) {
    signal(SIGCHLD, handle);
    int pid = fork();
    if (pid == 0) {
        sleep(5);
        exit(2);
    } else {
        wait(NULL);
    }
}


void handle() {
    puts("signal child");
}