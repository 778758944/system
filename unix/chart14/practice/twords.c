#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <ctype.h>

struct arg_set {
    char * fname;
    int count;
};

struct arg_set * mailbox;
void * countword(void * p);

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t flag = PTHREAD_COND_INITIALIZER;

int main(int argc, char ** argv) {
    int i, j, total = 0, num = 0;
    pthread_t arr[argc-1];

    for (i = 0; i < argc-1; i++) {
        pthread_t t;
        pthread_create(&t, NULL, countword, argv[i+1]);
        arr[i] = t;
    }

    while (num < i) {
        puts("dcdccdcd");
        pthread_cond_wait(&flag, &lock);
        puts("cdcdcd");
        total += mailbox->count;
        mailbox = NULL;
        pthread_cond_signal(&flag);
        num++;
    }

    printf("total is %d\n", total);

    return 0;
}


void * countword(void * p) {
    struct arg_set * arg = (struct arg_set *) p;
    FILE * fp;
    if ((fp = fopen(arg->fname, "r")) == NULL) {
        exit(1);
    }
    char c, prev;
    while ((c = getc(fp)) != EOF) {
        if (!isalnum(c) && isalnum(prev)) {
            arg->count++;
        }
        prev = c;
    }

    pthread_mutex_lock(&lock);

    if (mailbox != NULL) {
        pthread_cond_wait(&flag, &lock);
    }

    mailbox = arg;
    pthread_cond_signal(&flag);


    return NULL;
}



