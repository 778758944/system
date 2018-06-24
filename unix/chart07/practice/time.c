#include <stdio.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>

void handle() {
    puts("hello");
}

int main() {
    /* 毫秒 */
    struct itimerval newtimer;
    newtimer.it_value.tv_sec = 0;
    newtimer.it_value.tv_usec = 1000;
    newtimer.it_interval.tv_sec = 0;
    newtimer.it_interval.tv_usec = 2000;
    setitimer(ITIMER_REAL, &newtimer, NULL);
    signal(SIGALRM, handle);
    while(1) {
        pause();
    }
}