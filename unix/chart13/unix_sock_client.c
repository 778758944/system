#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/un.h>
#define SOCKNAME "/tmp/logfilesock"
#define oops(m) {perror(m); exit(1);}
#define MSGLEN 512

int main(int argc, char **argv) {
    int sock_id, rc;
    struct addrinfo * result, dint;
    memset(&dint, 0, sizeof(dint));
    dint.ai_family = AF_UNIX;
    dint.ai_socktype = SOCK_DGRAM;
    struct sockaddr_un addr;
    socklen_t addrlen;

    strcpy(addr.sun_path, SOCKNAME);
    addr.sun_family = AF_UNIX;

    addrlen = sizeof(addr.sun_family) + strlen(SOCKNAME);
    /*
    rc = getaddrinfo(SOCKNAME, NULL, &dint, &result);

    if (rc != 0) {
        oops(gai_strerror(rc));
    }
    */

    sock_id = socket(PF_UNIX, SOCK_DGRAM, 0);

    if (sock_id == -1) {
        oops("socket");
    }

    if (sendto(sock_id, argv[1], strlen(argv[1]), 0 , (struct sockaddr *) &addr, addrlen) == -1) {
        oops("send error");
    }


    
    return 0;
}