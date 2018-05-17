#include <stdio.h>
#include <ctype.h>
#include <pthread.h>
#include <stdlib.h>

 void * count_char(void * str);
 int total_count = 0;
 pthread_mutex_t counter_lock = PTHREAD_MUTEX_INITIALIZER;


 int main(int argc, char **argv) {
     if (argc != 3) {
         printf("Usage: %s file1 file2\n", argv[0]);
         exit(1);
     }

     pthread_t t1, t2;
     pthread_create(&t1, NULL, count_char, argv[1]);
     pthread_create(&t2, NULL, count_char, argv[2]);

     pthread_join(t1, NULL);
     pthread_join(t2, NULL);

     printf("total count is %d\n", total_count);

     return 0;


 }

 void * count_char(void * str) {
     char * file = (char *) str;
     FILE * fp;
     char c, prevc = '\0';
     if ((fp = fopen(file, "r")) == NULL) {
         exit(1);
     }

     while((c = fgetc(fp)) != EOF) {
         if (!isalnum(c) && isalnum(prevc)) {
             pthread_mutex_lock(&counter_lock);
             total_count++;
             pthread_mutex_unlock(&counter_lock);
         }
         prevc = c;
     }

     fclose(fp);

     return NULL;
 }
