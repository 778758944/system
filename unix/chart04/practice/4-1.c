#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>

#define oops(m) {perror(m); exit(1);}
#define I 0000400;
#define J 0400;
// 100000000

int main() {
    if (mkdir("./a/b", ACCESSPERMS) == -1) {
        oops("mkdir");
    }
    return 0;
}

