#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdlib.h>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>

#define oops(msg) {perror(msg); exit(1);}
#define BUFSIZE 100

int main(int argc, char **argv) {
    int sock_id;
    struct sockaddr_in saddr;
    struct hostent * hp;
    char message[BUFSIZE];
    int messagelen;
    struct addrinfo * result, hint;
    int rc;
    


    /*Step1: create a socket*/
    sock_id = socket(PF_INET, SOCK_STREAM, 0);

    if (sock_id == -1) {
        oops("create socket");
    }


    /*Step2: connect to server*/
    memset(&hint, 0, sizeof(hint));
    hint.ai_family = AF_INET;
    hint.ai_socktype = SOCK_STREAM;
    rc = getaddrinfo(argv[1], argv[2], &hint, &result);

    if (connect(sock_id, result->ai_addr, result->ai_addrlen) == -1) {
        oops("connect error:");
    }









    

    /*Step3: transfer data*/

    if ((messagelen = read(sock_id, message, BUFSIZE)) == -1) {
        oops("read");
    }

    if (write(1, message, messagelen) == -1) {
        oops("write");
    }

    close(sock_id);
    

    return 0;



}