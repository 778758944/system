#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#define PORT "13001"
#define oops(m) {perror(m); exit(1);}
#define SERVERNAME "xingwentao.xyz"
#define SERVERPORT "13000"
#define DIFF 5

int main() {
    int sock_id, request_id, sock_fd, request_fd;
    struct addrinfo * resultsrv, * resultclt, dint;
    int rc1, rc2, readc;
    char current[BUFSIZ];
    time_t t;

    memset(&dint, 0, sizeof(dint));
    dint.ai_family = AF_INET;
    dint.ai_socktype = SOCK_STREAM;

    rc1 = getaddrinfo(NULL, PORT, &dint, &resultsrv);
    rc2 = getaddrinfo(SERVERNAME, SERVERPORT, &dint, &resultclt);
    if (rc1 != 0 || rc2 != 0) {
        oops(gai_strerror(rc1));
    }

    sock_id = socket(PF_INET, resultsrv->ai_socktype, resultsrv->ai_protocol);
    request_id = socket(PF_INET, resultclt->ai_socktype, resultclt->ai_protocol); 

    if (bind(sock_id, resultsrv->ai_addr, resultsrv->ai_addrlen) == -1) {
        oops("bind:");
    }

    if (listen(sock_id, 1) == -1) {
        oops("listen:");
    }

    while(1) {
        sock_fd = accept(sock_id, NULL, NULL);
        time_t nowtime;
        nowtime = time(NULL);

        if (!t || (nowtime - t) > DIFF) {
            puts("time out");
            request_id = socket(PF_INET, resultclt->ai_socktype, resultclt->ai_protocol); 


            connect(request_id, resultclt->ai_addr, resultclt->ai_addrlen);
            if ((readc = read(request_id, current, BUFSIZ)) == -1) {
                oops("read");
            }

            printf("current is %s\n", current);
            fflush(stdout);
            t = nowtime;
            close(request_id);
        }

        if ((readc = write(sock_fd, current, strlen(current))) == -1) {
            oops("write");
        }
        close(sock_fd);
    }

}