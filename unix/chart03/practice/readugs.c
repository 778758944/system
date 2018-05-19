#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    if (argc != 2) {
        exit(1);
    }

    struct stat fileinfo;
    int mode;

    if (stat(argv[1], &fileinfo) == -1) {
        exit(1);
    }

    mode = fileinfo.st_mode;



    printf("set-uid: %d\n", (mode >> 2) & 01);
    printf("set-grp: %d\n", (mode >> 1) & 01);
    printf("strijy: %d\n", mode & 01);
    return 0;
}