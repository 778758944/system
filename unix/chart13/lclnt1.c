#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>
#include "./lclnt_funcs1.h"
#define oops(m) {perror(m); exit(1);}
void do_regular_work();
int main(int argc, char **argv) {
    if (argc != 3) {
        oops("error");
    }

    setup(argv[1], argv[2]);

    if(get_ticket() == -1) {
        oops("deny");
    }

    do_regular_work();
    release_ticket();

    return 0;
}

void do_regular_work() {
    puts("program start");
    sleep(10);
}