#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>


void * printMsg(void * msg);
void * printFunc(void * t);
int main() {
    pthread_t t;
    pthread_create(&t, NULL, printFunc, NULL);
    pthread_join(t, NULL);
    puts("out join");
    return 0;
}


void * printMsg(void * m) {
    char * msg = (char *) m;
    printf("%s", msg);
    sleep(1);
    return NULL;
}

void * printFunc(void * m) {
    pthread_t t;
    printf("hello");
    pthread_create(&t, NULL, printMsg, (void *) "world\n");
    pthread_join(t, NULL);
    puts("in join");

    return NULL;
}