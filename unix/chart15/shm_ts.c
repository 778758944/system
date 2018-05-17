#include <stdio.h>
#include <sys/shm.h>
#include <time.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define TIME_MEM_KEY 99
#define SEG_SIZE 100
#define oops(m) {perror(m); exit(1);}

int main() {
    int seg_id;
    char *mem_ptr;
    long now;
    int n;

    seg_id = shmget(TIME_MEM_KEY, SEG_SIZE, IPC_CREAT|0777);
    
    if (seg_id == -1) {
        oops("shmget");
    }

    mem_ptr = shmat(seg_id, NULL, 0);
    if (mem_ptr == (void *) -1) {
        oops("shmat");
    }

    for (n = 0; n < 60; n++) {
        time(&now);
        strcpy(mem_ptr, ctime(&now));
        sleep(1);
    }

    shmctl(seg_id, IPC_RMID, NULL);
}