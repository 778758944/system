#include <stdio.h>
#include <signal.h>
#include <unistd.h>
void weakup(int signum);

int main() {
    signal(SIGALRM, weakup);
    signal(SIGINT, weakup);
    puts("Good Night");
    alarm(4);
    pause();
    puts("Good Morning");
    return 0;
}

void weakup(int signum) {
    while(1) {
        putchar('\a');
    }
}