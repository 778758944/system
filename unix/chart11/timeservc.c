#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <strings.h>
#include <arpa/inet.h>
#include <time.h>


#define PORTNUM 13000
#define HOSTLEN 256
#define oops(msg) {perror(msg); exit(1);}

int main() {
    FILE * sock_fp;
    int sock_id, sock_fd;
    struct sockaddr_in saddr;
    char hostname[HOSTLEN];
    struct hostent *hp;
    time_t nowtime;
    struct addrinfo * result, hint;
    int rc;
    char *port = "13000";

    /* Step1: apply a socket (phone line) */
    sock_id = socket(PF_INET, SOCK_STREAM, 0);
    if (sock_id == -1) {
        oops("socket");
    }

    /*Step2: bind address and port to socket*/
    memset(&hint, 0, sizeof(hint));
    hint.ai_family = AF_INET;
    hint.ai_socktype = SOCK_STREAM;
    rc = getaddrinfo(NULL, port, &hint, &result);

    if (rc != 0) {
        oops(gai_strerror(rc));
    }

    if (bind(sock_id, result->ai_addr, result->ai_addrlen) != 0) {
        oops("bind error:");
    }

    freeaddrinfo(result);





















    /*
    bzero(&saddr, sizeof(saddr));
    gethostname(hostname, HOSTLEN); // return which sethostname
    saddr.sin_port = htons(PORTNUM);
    saddr.sin_family = AF_INET; // SET ADDRESS

    if(bind(sock_id, (struct sockaddr *)&saddr, sizeof(saddr)) != 0) {
        oops("bind");
    }
    */

    /* wait for call */
    if (listen(sock_id, 1) != 0) {
        oops("listen");
    }

    /* main loop: accept(), write(), close() */

    printf("preparetion done");

    while(1) {
        sock_fd = accept(sock_id, NULL, NULL);
        if (sock_fd == -1) {
            oops("accept");
        }

        sock_fp = fdopen(sock_fd, "w");
        nowtime = time(NULL);

        fprintf(sock_fp, "The time here is ...");
        fprintf(sock_fp, "%s", ctime(&nowtime));

        fclose(sock_fp);
    }

    return 0;


}