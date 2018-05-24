#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handle(int s);


int main() {
    char input[100];
    printf("%d\n", getpid());
    signal(SIGINT, handle);
    while(gets(input)) {
        puts(input);
    }

    return 0;
}

void handle(int s) {
    puts("receive signal");
}