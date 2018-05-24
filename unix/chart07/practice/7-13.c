#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#define oops(m) {perror(m); exit(1);}
#define DIFF 10

int main(int argc, char ** argv) {
    if (argc < 3) {
        oops("Usage:");
    }
    int pid;
    long t;
    int tty;
    struct stat info;
    long lastmodify;
    long nowtime;
    if (stat("/dev/ttys001", &info) != 0) {
        oops("stat error:");
    }
    sscanf(argv[1], "%d", &pid);
    sscanf(argv[2], "%ld", &t);
    printf("pid is %d, time is %ld\n", pid, t);
    while (t < DIFF) {
        sleep(t);
        stat("/dev/ttys001", &info);
        lastmodify = (long) info.st_mtimespec.tv_sec;
        time(&nowtime);
        t = nowtime - lastmodify;
        puts("loop");
    }
    kill(pid, SIGKILL);
}