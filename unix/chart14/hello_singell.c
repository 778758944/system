#include <stdio.h>
#include <unistd.h>
#define NUM 5

void printf_msg(char *);

int main() {
    printf_msg("hello\n");
    printf_msg("world\n");
}

void printf_msg(char *m) {
    int i;
    for(i = 0; i < NUM; i++) {
        printf("%s", m);
        fflush(stdout);
        sleep(1);
    }
}