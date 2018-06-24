#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdlib.h>
#include <ctype.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t flag = PTHREAD_COND_INITIALIZER;



struct arg_set {
    char * fname;
    int count;
};

void * count_word(void * p);
struct arg_set * mailbox;

int main(int argc, char **argv) {
    int total;
    if(argc != 3) {
        exit(1);
    }

    struct arg_set arg1, arg2;
    pthread_t t1, t2;
    int num = 0;

    // set a lock with lock, lock is the id of this lock
    pthread_mutex_lock(&lock);

    arg1.fname = argv[1];
    arg1.count = 0;
    pthread_create(&t1, NULL, count_word, &arg1);

    arg2.fname = argv[2];
    arg2.count = 0;
    pthread_create(&t2, NULL, count_word, &arg2);

    while(num < 2) {
        puts("MAIN: waiting for a flag to go up");
        // stop the pthread, wait for another thread signal
        // will unlock the lock by pthread_mutex_lock
        pthread_cond_wait(&flag, &lock);
        puts("flag was rised, I have the lock");
        printf("%d, %s\n", mailbox->count, mailbox->fname);
        total += mailbox->count;

        if (mailbox == &arg1) {
            pthread_join(t1, NULL);
        }

        if (mailbox == &arg2) {
            pthread_join(t2, NULL);
        }

        mailbox = NULL;
        pthread_cond_signal(&flag);
        num++;
    }

    printf("%d words\n", total);
    return 0;
}


void * count_word(void * p) {
    struct arg_set * ptr = (struct arg_set *) p;
    FILE * fp;
    char c, prevc;
    int count = 0;

    if ((fp = fopen(ptr->fname, "r")) == NULL) {
        exit(1);
    }

    while((c = fgetc(fp)) != EOF) {
        if (!isalnum(c) && isalnum(prevc)) {
            ptr->count++;
        }
        prevc = c;
    }

    fclose(fp);

    puts("COUNT: waiting to get lock");
    pthread_mutex_lock(&lock);

    if (mailbox != NULL) {
        pthread_cond_wait(&flag, &lock);
    }

    mailbox = ptr;
    puts("COUNT: raise the flag");
    pthread_cond_signal(&flag);
    printf("COUNT: unlocking box");
    pthread_mutex_unlock(&lock);

    return NULL;



}

