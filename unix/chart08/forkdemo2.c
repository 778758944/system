#include <stdio.h>
#include <unistd.h>

int main() {
    printf("mypid is %d\n", getpid());
    fork();
    fork();
    fork();
    printf("mypid id %d\n", getpid());
    return 0;
}