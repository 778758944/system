#include "./popen.h"
FILE * mypopen(const char * command, const char * mode) {
    int pfp[2], pid;
    FILE * fp;
    int child_end, parent_end;

    if (*mode == 'r') {
        parent_end = READ;
        child_end = WRITE;
    } else if (*mode == 'w') {
        parent_end = WRITE;
        child_end = READ;
    } else {
        return NULL;
    }

    if (pipe(pfp) == -1) {
        exit(1);
    }

    if ((pid = fork()) == -1) {
        exit(1);
    }
    /*parent code*/
    if (pid > 0) {
        return fdopen(pfp[parent_end], mode);
    }

    /*child code*/
    if (dup2(pfp[child_end], child_end) == -1) {
        exit(1);
    }

    if (close(pfp[child_end]) == -1) {
        exit(1);
    }

    execl("/bin/sh", "sh", "-c", command, NULL);
    exit(1);

}