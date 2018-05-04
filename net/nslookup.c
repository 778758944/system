#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <errno.h>
#include <strings.h>
#include <stdio.h>
#define HOSTSIZE 30

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <domain name>", argv[0]);
        exit(1);
    }
    struct addrinfo *result, *p;
    struct addrinfo hint;
    int rc, rc2;
    char host[HOSTSIZE];

    memset(&hint, 0, sizeof(hint));

    hint.ai_family = AF_INET;
    hint.ai_socktype = SOCK_STREAM;

    rc = getaddrinfo(argv[1], NULL, &hint, &result);
    if (rc != 0) {
        perror(gai_strerror(rc));
        exit(1);
    }

    p = result;

    while(p) {
        rc2 = getnameinfo(p->ai_addr, p->ai_addrlen, host, HOSTSIZE, NULL, 0, NI_NUMERICHOST);
        if (rc2 != 0) {
            perror(gai_strerror(rc2));
            exit(1);
        }

        printf("%s\n", host);
        p = p->ai_next;
    }

    freeaddrinfo(result);
    return 0;

}