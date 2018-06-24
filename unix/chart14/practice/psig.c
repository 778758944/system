#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t flag = PTHREAD_COND_INITIALIZER;
int i = 0;
void * func(void *);
int main() {

    pthread_t t;

    pthread_mutex_lock(&lock);

    pthread_create(&t, NULL, func, NULL);

    

    pthread_cond_wait(&flag, &lock);

    printf("i is %d\n", i);

    return 0;
    
    
}

void * func(void * ptr) {
    sleep(5);
    pthread_mutex_lock(&lock);

    i++;

    pthread_cond_signal(&flag);
    pthread_mutex_unlock(&lock);

    return NULL;

}