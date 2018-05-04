#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
void inithandle(int s);
void quithandle(int s);
int main() {
    char input[100];
    signal(SIGINT, inithandle);
    signal(SIGQUIT, quithandle);
    while(gets(input)) {
        if (strcmp(input, "quit") == 0) {
            exit(1);
        }
        puts(input);
    }
}


void inithandle(int s) {
    printf("reciving signal %d waiting\n", s);
    sleep(2);
    puts("leave inithandle");
}

void quithandle(int s) {
    printf("reciving signal %d wating\n", s);
    sleep(10);
    puts("leave quithandle");
}


