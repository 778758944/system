#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM 5

void * printf_msg(void *);

int main() {
    pthread_t t1, t2;
    
    pthread_create(&t1, NULL, printf_msg, (char *) "hello");
    pthread_create(&t2, NULL, printf_msg, (char *) "world\n");

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}

void * printf_msg(void *m) {
    char *msg = (char *) m;
    int i;
    for(i = 0; i < NUM; i++) {
        printf("%s", msg);
        fflush(stdout);
        sleep(1);
    }
    return NULL;
}