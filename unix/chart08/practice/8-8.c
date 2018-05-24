#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

void child_process();
int create_process();

int main(int argc, char **argv) {
    int childpid1, childpid2;
    int waitpid;
    int i;
    int j = 0;
    int max;

    sscanf(argv[1], "%d", &max);
    // childpid1 = fork();


    for (i = 0; i < max; i++) {
        puts("loop start");
        int cpid = fork();
        int childp;
        if (cpid) {
            // childp = wait(NULL);
            // printf("child process %d is done\n", childp);
        } else {
            child_process();
        }
    }

    
/*
    if (childpid1 == 0) {
        child_process();
    } else {
        childpid2 = fork();
        if (childpid2 == 0) {
            child_process();
        } else {
            waitpid = wait(NULL);
            printf("child process %d is done\n", waitpid);
        }
    }
    */

//    create_process();
//    puts("hahah");

    while(j < i) {
        int cpid = wait(NULL);
        printf("child process %d is done\n", cpid);
        j++;
    }
    
}

void child_process() {
    sleep(5);
    exit(2);
}

int create_process() {
    int cpid = fork();
    printf("cpid is %d\n", cpid);
    return cpid;
}

