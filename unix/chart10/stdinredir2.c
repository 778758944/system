#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

// #define USE_DUP2

int main() {
    int newfd;
    char line[100];
    int fd;

    fgets(line, 100, stdin); printf("line is %s", line);
    fgets(line, 100, stdin); printf("line is %s", line);
    fgets(line, 100, stdin); printf("line is %s", line);

    fd = open("./data", O_RDONLY);

    #ifdef USE_DUP2
        close(0);
        newfd = dup(fd); /* 复制链接，自动绑定到最低文件描述符 */
    #else
        newfd = dup2(fd, 0);
    #endif

    if (newfd != 0) {
        fprintf(stderr, "could not duplicate fd to 0\n");
        exit(1);
    }

    close(fd);

    fgets(line, 100, stdin); printf("line is %s", line);
    fgets(line, 100, stdin); printf("line is %s", line);
    fgets(line, 100, stdin); printf("line is %s", line);
}