#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#define NUM 5
int counter = 0;

void * printf_c() {
    int i;
    for (i = 0; i < NUM; i++) {
        printf("counter is %d\n", counter);
        sleep(1);
    }

    return NULL;
}

int main() {
    int i;
    pthread_t t1;

    if (pthread_create(&t1, NULL, printf_c, NULL) != 0) {
        exit(1);
    }

    for (i = 0; i < NUM; i++) {
        counter ++;
        sleep(1);
    }

    // pthread_join(t1, NULL);
    return 0;

    




}