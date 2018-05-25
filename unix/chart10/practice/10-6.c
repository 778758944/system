#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#define MSG "Hello, World\n"

int main() {
    int fd, i = 0;
    close(0);

    fd = open("/dev/ttys001", O_WRONLY);

    while(i < 10) {
        write(0, MSG, strlen(MSG));
        i++;
    }

    return 0;
}