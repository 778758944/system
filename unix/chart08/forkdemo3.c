#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handle(int num) {
    int c;
    puts("kill child process");
    while ((c = waitpid(-1, NULL, WNOHANG)) > 0) {
        printf("pid %d\n", c);
    }
}

int main() {
    int pid[3] = {}, i;
    signal(SIGCHLD, handle);

    for(i = 0; i < 3; i++) {
        int pid;
        pid = fork();

        if (pid == 0) {
            execlp("/bin/date","date", NULL);
        } else {
            printf("pid is %d\n", pid);
        }
    }

    // wait(NULL);

    while(getchar()) {

    }

    return 0;
}