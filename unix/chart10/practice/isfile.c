#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main() {
    int pd[2];
    int fd, isfile1, isfile2;
    struct stat finfo, pinfo;

    if (pipe(pd) == -1) {
        exit(1);
    }


    fd = open("./sortfile", O_RDONLY);

    fstat(pd[0], &pinfo);
    fstat(fd, &finfo);

    isfile1 = S_ISREG(finfo.st_mode);
    isfile2 = S_ISREG(pinfo.st_mode);

    printf("isfile1 = %d, isfile2 = %d\n", isfile1, isfile2);
    return 0;
}
