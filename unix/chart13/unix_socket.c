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
#define oops(m) {perror(m); exit(1);}
#define MSGLEN 512


int main() {
    char sockname[] = "/tmp/logfilesock";
    struct addrinfo *result, dint;
    int rc, sock_id, l;
    memset(&dint, 0, sizeof(dint));
    dint.ai_family = PF_UNSPEC;
    dint.ai_socktype = SOCK_DGRAM;
    char msg[MSGLEN];
    time_t now;
    char * timestr;
    struct sockaddr_un addr;
    socklen_t addrlen;
    /*
    rc = getaddrinfo(sockname, NULL, &dint, &result);

    if (rc != 0) {
        oops(gai_strerror(rc));
    }
    */
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, sockname);

    addrlen = strlen(sockname) + sizeof(addr.sun_family);


    sock_id = socket(PF_UNIX, SOCK_DGRAM, 0);

    if (sock_id == -1) {
        oops("sock");
    }

    if (bind(sock_id, (struct sockaddr *) &addr, addrlen) == -1) {
        oops("bind");
    }

    while(1) {
        l = read(sock_id, msg, MSGLEN);
        msg[l] = '\0';
        time(&now);
        timestr = ctime(&now);
        timestr[strlen(timestr) - 1] = '\0';
        printf("%s %s\n", timestr, msg);
        fflush(stdout);
    }

    return 0;
}