#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int fd;
    char line[100];

    fgets(line, 100, stdin); printf("line is %s\n", line);
    fgets(line, 100, stdin); printf("line is %s\n", line);
    fgets(line, 100, stdin); printf("line is %s\n", line);


    close(0);

    fd = open("/etc/passwd", O_RDONLY);

    if (fd != 0) {
        printf("error to open file");
        exit(1);
    }

    fgets(line, 100, stdin); printf("line is %s\n", line);
    fgets(line, 100, stdin); printf("line is %s\n", line);
    fgets(line, 100, stdin); printf("line is %s\n", line);
}