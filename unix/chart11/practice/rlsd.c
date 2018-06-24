#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#define PORT "13001"
#define oops(m) {perror(m); exit(1);}


int main() {
    struct addrinfo * result, dint;
    int rc, sock_id, sock_fd, pid;
    FILE * fp;
    char dirname[BUFSIZ];
    char content[BUFSIZ];
    int readc;
    int ppd[2];

    memset(&dint, 0, sizeof(dint));
    dint.ai_family = AF_INET;
    dint.ai_socktype = SOCK_STREAM;
    
    rc = getaddrinfo(NULL, PORT, &dint, &result);

    if (rc != 0) {
        oops(gai_strerror(rc));
    }

    sock_id = socket(PF_INET, result->ai_socktype, result->ai_protocol);

    if (sock_id == -1) {
        oops("socket:");
    }

    if (bind(sock_id, result->ai_addr, result->ai_addrlen) == -1) {
        oops("bind:");
    }

    if (listen(sock_id, 1) == -1) {
        oops("listen:");
    }

    if (pipe(ppd) == -1) {
        oops("pipe:");
    }

    while(1) {
        sock_fd = accept(sock_id, NULL, NULL);
        if (sock_fd == -1) {
            continue;
        }

        if ((readc = read(sock_fd, dirname, BUFSIZ)) == -1) {
            oops("read error");
        }

        pid = fork();


        if (pid > 0) {
            puts("main process");
            wait(NULL);
            if ((readc = read(ppd[0], content, BUFSIZ)) == -1) {
                oops("read error");
            }
            puts("after read from child process");

            // printf("content is %s\n", content);
            // fflush(stdout);
            write(sock_fd, content, readc);
        } else {
            dup2(ppd[1], 1);
            execlp("ls", "ls", dirname, NULL);
            oops("child process error:");
        }
        close(sock_fd);
    }

}
