#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <ctype.h>

struct arg_set {
    char * fname;
    int count;
};
void * countword(void * p);

int main(int argc, char **argv) {
   struct arg_set set1, set2;
   pthread_t t;

   set1.fname = argv[1];
   set1.count = 0;

   set2.fname = argv[2];
   set2.count = 0;

   countword(&set1);

   pthread_create(&t, NULL, countword, &set2);

   pthread_join(t, NULL);

   printf("char is %d\n", set1.count + set2.count);
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

