#include <stdio.h>
#include <aio.h>

void handleInput();
static char input[1];
static struct aiocb aiobuf;
int main() {
    aiobuf.aio_fildes = 0;
    aiobuf.aio_buf = input;
    aiobuf.aio_nbytes = 1;
    aiobuf.aio_offset = 0;

    aiobuf.aio_sigevent.sigev_notify = SIGEV_SIGNAL;
    aiobuf.aio_sigevent.sigev_signo = SIGIO;
    signal(SIGIO, handleInput);
    aio_read(&aiobuf);
    while(1) {}
}


void handleInput() {
    puts("sigio start");
    printf("%s\n", aiobuf.aio_buf);
}