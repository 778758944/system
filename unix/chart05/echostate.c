#include <stdio.h>
#include <termios.h>
#include <errno.h>

int main() {
    struct termios info;
    if (tcgetattr(0, &info) == -1) {
        perror("error:");
    }


    if (info.c_lflag & ECHO) {
        puts("echo on");
    } else {
        puts("echo off");
    }

    return 0;
}