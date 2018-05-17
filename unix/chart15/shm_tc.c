#include <stdio.h>
#include <sys/shm.h>
#include <time.h>
#include <errno.h>
#include <stdlib.h>

#define TIME_MEM_KEY 99
#define SEG_SIZE 100
#define oops(m) {perror(m); exit(1);}


int main() {
    int seg_id;
    char * mem_ptr;
    long now;

    seg_id = shmget(TIME_MEM_KEY, SEG_SIZE, 0777);
    if (seg_id == -1) {
        oops("shmget");
    }

    mem_ptr = shmat(seg_id, NULL, 0);
    if (mem_ptr == (void *) -1)
        oops("shmat");
    printf("The time, direct from mem %s", mem_ptr);

    shmdt(mem_ptr);
    return 0;
}