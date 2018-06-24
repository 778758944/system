#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#define HOSTNAME "0.0.0.0"
#define PORT "13000"
#define oops(m) {perror(m); exit(1);}

int main() {
    struct addrinfo *result, dint;
    int rc, rc2;
    int sock_id, sock_fd;
    time_t t;
    FILE * fp;
    struct sockaddr info;
    char clienthost[BUFSIZ];
    char clientport[BUFSIZ];
    unsigned int len = sizeof(info);


    memset(&dint, 0, sizeof(dint));
    dint.ai_family = AF_INET;
    dint.ai_socktype = SOCK_STREAM;

    rc = getaddrinfo(NULL, PORT, &dint, &result);


    if (rc != 0) {
        oops(gai_strerror(rc));
    }


    sock_id = socket(PF_INET, SOCK_STREAM, 0);


    if (sock_id == -1) {
        oops("create socket");
    }


    if (bind(sock_id, result->ai_addr, result->ai_addrlen) == -1) {
        oops("bind:");
    }

    free(result);

    if (listen(sock_id, 1) == -1) {
        oops("listen:");
    }

    while(1) {
        sock_fd = accept(sock_id, &info, &len);
        rc2 = getnameinfo(&info, sizeof(info), clienthost, BUFSIZ, clientport, BUFSIZ, NI_NUMERICHOST);
        if (rc2 != 0) {
            oops(gai_strerror(rc2));
        }

        printf("client ip %s, port %s\n", clienthost, clientport);
        fp = fdopen(sock_fd, "w");
        if (fp == NULL) {
            oops("fdopen error:");
        }
        t = time(NULL);
        // char * timestr = ctime(&t);
        
        fprintf(fp, "time: %s\n", ctime(&t));
        fflush(fp);
        // write(sock_fd, ctime(&t), s);
        fclose(fp);
        // close(sock_fd);
    }

    return 0;




}