#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

static char str[100];
static int i = 0;
void handle(int s);

int main(int argc, char **argv) {
    if (argc < 2) {
        exit(1);
    }

    sscanf(argv[1], "%s", str);
    signal(SIGINT, handle);
    while(1){
        
    }
    return 0;
}

void handle(int s) {
    i++;
    if (i == 10) {
        printf("%s\n", str);
        i = 0;
    }
}