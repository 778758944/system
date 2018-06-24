#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>


int main() {
    int fd, fd2;
    struct stat fileinfo;
    char p[3];

    fd = open("./main.c", O_RDONLY);

    lseek(fd, 1, SEEK_SET);

    read(fd, p, 2);
    p[2] = '\0';



    printf("data is %s\n", p);
    return 0;
}