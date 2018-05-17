#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include "./dgram.h"

#define oops(m) {perror(m); exit(1);}

int main(int argc, char **argv) {
    if (argc != 4) {
        oops("Usage:");
    }
    int sock_id, c, msg_len;
    struct addrinfo * result, dint;
    char buf[BUFSIZ];

    memset(&dint, 0, sizeof(dint));
    dint.ai_socktype = SOCK_DGRAM;
    dint.ai_family = AF_INET;

    c = getaddrinfo(argv[1], argv[2], &dint, &result);

    if (c != 0) {
        oops("get error");
    }

    sock_id = make_dgram_client_socket();

    if (sock_id == -1) {
        oops("sock error:");
    }

    if (sendto(sock_id, argv[3], strlen(argv[3]), 0, result->ai_addr, result->ai_addrlen) == -1) {
        oops("sendto error");
    }

    if ((msg_len = recvfrom(sock_id, buf, BUFSIZ, 0, NULL, 0)) != -1) {
        buf[msg_len] = '\0';
        printf("backmsg: %s", buf);
    }

    return 0;


}