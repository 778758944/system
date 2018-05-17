#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>


#define oops(m) {perror(m); exit(1);}
#define TIME_MEM_KEY 99
#define TIME_SEM_KEY 9900
#define SIGSIZE 100

int semset_id, shmid;



void set_sem_value(int semset_id, int semnum, int val);
void wait_and_lock(int semid);
void release_lock(int semid);
void cleanup(int n);
int main() {
    /*
    1. sem key
    2. num of sem
    3. flag
    */
    char * mem_ptr;
    time_t now;
    int n;
    semset_id = semget(TIME_SEM_KEY, 2, (0666|IPC_CREAT|IPC_EXCL));

    shmid = shmget(TIME_MEM_KEY, SIGSIZE, IPC_CREAT|0777);
    mem_ptr = shmat(shmid, NULL, 0);

    set_sem_value(semset_id, 0, 0);
    set_sem_value(semset_id, 1, 0);

    signal(SIGINT, cleanup);

    if (mem_ptr == (void *)-1) {
        oops("shmat");
    }

    for(n = 0; n < 60; n++) {
        time(&now);
        printf("waiting for lock");
        wait_and_lock(semset_id);
        printf("updating memory");
        strcpy(mem_ptr, ctime(&now));
        sleep(5);
        release_lock(semset_id);
        printf("release lock");
        sleep(1);
    }

    cleanup(n);
}

void set_sem_value(int semset_id, int semnum, int val) {
    union semun initval;
    initval.val = val;
    /*
    1.siganl set id
    2.specific num of signal
    3.command
    4.command argument
    */
    if (semctl(semset_id, semnum, SETVAL, initval) == -1) {
        oops("semctl");
    }
}


void wait_and_lock(int semset_id) {
    struct sembuf actions[2];
    /*readers*/
    actions[0].sem_num = 0;
    actions[0].sem_flg = SEM_UNDO;
    actions[0].sem_op = 0;
    /*writers*/
    actions[1].sem_num = 1;
    actions[1].sem_flg = SEM_UNDO;
    actions[1].sem_op = +1;

    if (semop(semset_id, actions, 2) == -1) {
        oops("semop: locking");
    }


}

void release_lock(int semid) {
    struct sembuf actions[1];
    actions[0].sem_num = 1;
    actions[0].sem_flg = SEM_UNDO;
    actions[0]. sem_op = -1;
    if (semop(semid, actions, 1) == -1) {
        oops("semop: unlock");
    }
}

void cleanup(int n) {
    shmctl(shmid, IPC_RMID, NULL);
    semctl(semset_id, 0, IPC_RMID, NULL);
}


