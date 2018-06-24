#include <stdio.h>
#include <unistd.h>
#include "../socketlib.h"
#include <errno.h>
#include <stdlib.h>
#define oops(m) {perror(m); exit(1);}
#define PORT "13000"

int main() {
    int sock_id, sock_fd, pid;
    int pp[2];

    sock_id = make_server_socket(PORT);
    pipe(pp);

    while(1) {
       sock_fd = accept(sock_id, NULL, NULL);

       pid = fork();

       if (pid == 0) {
           dup2(sock_fd, 1);
        //    execlp("date", "date", NULL);
           write(1, "hello,world", 13);
           oops("fork error");
       } else {
           wait(NULL);
           close(sock_fd);
       }

        
    }
}