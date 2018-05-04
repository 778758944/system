#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAXARGV 20
#define LEN 100

void execute(char **argv);
char * makestring(char * buf);

int main(){
    int enterTimes = 0;
    char * argv[MAXARGV];
    char buf[100];

    while (enterTimes < MAXARGV) {
        if (fgets(buf, LEN, stdin) != NULL && buf[0] != '\n') {
            argv[enterTimes] = makestring(buf);
            enterTimes++;
        } else {
            if (enterTimes > 0) {
                argv[enterTimes] = 0;
                execute(argv);
                enterTimes = 0;
            }
        }
    }

    return 0;
}


void execute(char **argv) {
    char * fname = argv[0];
    printf("fname %s\n", fname);
    execvp(fname, argv);
}

char * makestring(char * buf) {
    buf[strlen(buf) - 1] = '\0'; // trim new line
    char * str = (char *) malloc(strlen(buf) + 1); // not stack memory
    if (str == NULL) {
        perror("error:");
        exit(1);
    }
    strcpy(str, buf);
    return str; //so can be reutrned
}

