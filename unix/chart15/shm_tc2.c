#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <sys/types.h>


#define oops(m) {perror(m); exit(1);}
#define TIME_MEM_KEY 99
#define TIME_SEM_KEY 9900
#define SIGSIZE 100

void wait_and_lock(int sem_id);
void release_lock(int sem_id);

int main() {
    int shm_id, sem_id;
    char * mem_ptr;
    char buf[BUFSIZ];

    shm_id = shmget(TIME_MEM_KEY, SIGSIZE, 0666);
    sem_id = semget(TIME_SEM_KEY, 2, 0666);

    mem_ptr = shmat(shm_id, NULL, 0);

    if (mem_ptr == (void *) -1) {
        oops("error");
    }

    wait_and_lock(sem_id);
    printf("time is %s\n", mem_ptr);
    release_lock(sem_id);

    return 0;


    
}

void wait_and_lock(int sem_id) {
    struct sembuf actions[2];
    actions[0].sem_num = 1;
    actions[0].sem_flg = SEM_UNDO;
    actions[0].sem_op = 0;

    actions[1].sem_num = 0;
    actions[1].sem_flg = SEM_UNDO;
    actions[1].sem_op = +1;

    if (semop(sem_id, actions, 2) == -1) {
        oops("semop: locking");
    }
}

void release_lock(int semset_id) {
    struct sembuf actions[1];
    actions[0].sem_num = 0;
    actions[0].sem_flg = SEM_UNDO;
    actions[0].sem_op = -1;

    if (semop(semset_id, actions, 1) == -1) {
        oops("semop: locking");
    }
}






