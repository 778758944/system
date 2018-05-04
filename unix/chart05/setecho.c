#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#define oops(s, x) {perror(s); exit(x);}

int main(int argc, char ** argv) {
    if (argc < 3) {
        oops(argv[2], 1);
    }

    int fp = 0;
    struct termios info;

    if ((fp = open(argv[1], O_WRONLY)) == -1) {
        oops("open error:", 1);
    }

    if (tcgetattr(fp, &info) == -1) {
        oops("get error:", 1);
    }

    if (argv[2][0] == 'y') {
        info.c_lflag |= ECHO;
    } else {
        info.c_lflag &= ~ECHO;
    }

    if (tcsetattr(fp, TCSANOW, &info) == -1) {
        oops("set error:", 1);
    }


    return 0;
}