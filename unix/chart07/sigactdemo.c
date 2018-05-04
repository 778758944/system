#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
void inithandle(int s);
int main() {
    struct sigaction newhandle;
    char input[100];
    sigset_t blocked;

    newhandle.sa_flags = SA_RESETHAND | SA_RESTART;
    newhandle.__sigaction_u.__sa_handler = inithandle;
    sigemptyset(&blocked);
    sigaddset(&blocked, SIGQUIT);
    newhandle.sa_mask = blocked;

    if (sigaction(SIGINT, &newhandle, NULL) == -1) {
        perror("error:");
    }

    while(gets(input)) {
        puts(input);
    }


}

void inithandle(int s) {
    printf("Called with signal %d\n", s);
    sleep(5);
    printf("done handling signal %d\n", s);
}