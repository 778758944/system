#include <stdio.h>
#include <signal.h>
#include <unistd.h>
int main() {
    sigset_t sigs, prevsigs;
    sigemptyset(&sigs);
    sigaddset(&sigs, SIGINT);
    // add block
    sigprocmask(SIG_BLOCK, &sigs, &prevsigs);
    sleep(5);
    puts("release");
    // sigprocmask(SIG, &prevsigs, NULL);
    return 0;
}