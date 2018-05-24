#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>

#define MAX_LEN 100

void my_handler(int signum)
{
    char data[MAX_LEN];
    int len;

    len = read(STDIN_FILENO, &data, MAX_LEN);
    data[len] = 0;
    
    printf("Input message: %s\n", data);
    exit(0);
}

int main(void)
{
    int oflags;

    /* set new SIGIO handler */
    signal(SIGIO, my_handler);
    /* set fd's owner process */
    fcntl(STDIN_FILENO, F_SETOWN, getpid());
    /* get old fd flags */
    oflags = fcntl(STDIN_FILENO, F_GETFL);
    /* set new fd flags */
    fcntl(STDIN_FILENO, F_SETFL, oflags | O_ASYNC);

    /* infinitely wait until recv SIGIO */
    while(1);
    return 0;
}