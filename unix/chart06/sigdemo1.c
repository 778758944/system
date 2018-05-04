#include <signal.h>
#include <stdio.h>
#include <unistd.h>
void f(int);
int main() {
    int i;
    signal(SIGINT, f);
    for (i = 0; i < 5; i++) {
        printf("hello\n");
        sleep(1);
    }
}

void f(int signum) {
    printf("OUCH! \n");
}