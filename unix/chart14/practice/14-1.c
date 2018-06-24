#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

void * printMsg(void * msg);
int main() {
    pthread_t t1, t2, t3;

    pthread_create(&t1, NULL, printMsg, (void *) "test1\n");
    pthread_create(&t2, NULL, printMsg, (void *) "test11\n");
    pthread_create(&t3, NULL, printMsg, (void *) "test111\n");

    pthread_join(t1, NULL);
    puts("after t1 join");
    pthread_join(t2, NULL);
    puts("after t2 join");
    pthread_join(t3, NULL);
    puts("after t3 join");
    return 0;
}


void * printMsg(void * m) {
    char * msg = (char *) m;
    int len = strlen(msg);
    int i;
    for (i = 0; i < len; i++) {
        printf("%s", msg);
        fflush(stdout);
        sleep(1);
    }
    return NULL;
}


