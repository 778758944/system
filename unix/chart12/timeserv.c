#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "./socketlib.h"
#define oops(m) {perror(m); exit(1);}

void signal_handle() {
    sleep(3);
    puts("handle signal");
}


int main() {
    int sock, sock_fp, pid;
    sock = make_server_socket("13000");
    char *message = "hello, world";
    if (sock == -1) {
        oops("error");
    }

    signal(SIGINT, signal_handle);

    while(1) {
        sock_fp = accept(sock, NULL, NULL);
        if (sock_fp == -1) {
            oops("error");
        }

        pid = fork();

        if (pid == -1) {
            oops("error");
        } else if (pid == 0) {
            dup2(sock_fp, 1);
            close(sock_fp);
            execlp("/bin/date", "date", NULL);
            oops("execlp");
        } else {
            wait(NULL);
            close(sock_fp);
        }
        // close(sock_fp);


    }
}