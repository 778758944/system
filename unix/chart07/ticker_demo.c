#include <stdio.h>
#include <sys/time.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
void cutdown(int signum);
int set_ticker(int n_msecs);
int main() {
    signal(SIGALRM, cutdown);
    if (set_ticker(500) == -1) {
        perror("error:");
        exit(0);
    }

    while(1) {
        pause();
    }

    return 0;


}

void cutdown(int signum) {
    static int num = 10;
    printf("%d\n", num--);
    fflush(stdout);
    if (num < 0) {
        printf("DONE! \n");
        exit(0);
    }
}

int set_ticker(int n_msecs) {
    struct itimerval new_timeset;
    long n_sec, n_usec;

    n_sec = n_msecs/1000;
    n_usec = (n_usec % 1000) * 1000L;

    new_timeset.it_interval.tv_sec = n_sec;
    new_timeset.it_interval.tv_usec = n_usec;

    new_timeset.it_value.tv_sec = n_sec;
    new_timeset.it_value.tv_usec = n_usec;

    return setitimer(ITIMER_REAL, &new_timeset, NULL);
}



