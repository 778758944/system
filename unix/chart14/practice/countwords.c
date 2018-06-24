#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <ctype.h>

struct arg_set {
    char * fname;
    int count;
};

void * countword(void * p);

int main(int argc, char **argv) {
    pthread_t arr[argc-1];
    struct arg_set * argarr[argc-1];
    int i, j, total = 0;
    for(i = 0; i < (argc - 1); i++) {
        pthread_t t;
        struct arg_set * ptr = (struct arg_set *) malloc(sizeof(struct arg_set));
        ptr->fname = argv[i + 1];
        ptr->count = 0;
        pthread_create(&t, NULL, countword, ptr);
        arr[i] = t;
        argarr[i] = ptr;
    }

    puts("create pthread");

    for(j = 0; j < i; j++) {
        pthread_join(arr[j], NULL);
    }

    puts("after join");

    for(j = 0; j < i; j++) {
        total += argarr[j]->count;
    }

    puts("after add");

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
    return NULL;
}