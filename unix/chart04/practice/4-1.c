#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>

#define oops(m) {perror(m); exit(1);}

int main() {
    if (mkdir("./test", DEFFILEMODE) == -1) {
        oops("mkdir");
    }
    return 0;
}