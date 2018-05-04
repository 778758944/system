#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include "./splitline.h"

#define MAXARGV 100
#define LEN 100


int pid;


char * makestring(char * buf);
void execute(char **argv);
void testSig(int signum);

int main() {
    char buf[LEN];
    int enterTimes = 0;
    char **argv; // can store MAXARGV pointers that point to char
    while (enterTimes < MAXARGV) {
        if (fgets(buf, LEN, stdin) != NULL && buf[0] != '\n') {
            // argv[enterTimes] = makestring(buf);
            // enterTimes++;
            argv = splitline(buf);
            execute(argv);
        }
    }
    return 0;
}




char * makestring(char * buf) {
    char * cp;
    /*trim new line*/
    buf[strlen(buf) - 1] = '\0';
    cp = (char *) malloc(strlen(buf) + 1);
    if (cp == NULL) {
        perror("error:");
        exit(1);
    }
    strcpy(cp, buf);
    return cp;
}

void execute(char **argv) {
    int status;

    pid = fork();

    if (pid == -1) {
        perror("error:");
        exit(1);
    } else if (pid == 0) {
        // signal(SIGINT, testSig);
        char * fname = argv[0];
        execvp(fname, argv);
        // pay attention here
        perror("error:");
        exit(1);
    } else {
        signal(SIGINT, testSig);
        int waitForPid;
        waitForPid = wait(&status);
        printf("child process exit with %d\n", status >> 8);
    }

    
}

void testSig(int num) {
    printf("pid %d signal capture\n", pid);
}