#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#define DELAY 10
void child_code(int);
void parent_code(int);
int main() {
    int newpid;

    printf("my pid is %d \n", getpid());

    if ((newpid = fork()) == -1) {
        perror("fork");
    } else if (newpid == 0) {
        child_code(DELAY);
    } else {
        parent_code(newpid);
    }

}

void child_code(int delay) {
    printf("child %d here, will sleep for %d seconds\n", getpid(), delay);
    sleep(delay);
    printf("child done, about to exit\n");
    exit(10);
}

void parent_code(int pid) {
    int wait_rv, status;
    int high8, low7, bit7;
    wait_rv = wait(&status);
    printf("done waitting for %d, Wait returned %d\n", pid, wait_rv);
    high8 = status >> 8;
    low7 = status & 0x7f;
    bit7 = status & 0x80;
    printf("status: exit=%d, sig=%d, core=%d\n", high8, low7, bit7);
}