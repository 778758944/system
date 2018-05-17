#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include "./dgram.h"

#define oops(m) {perror(m); exit(1);}

void say_who_called(struct sockaddr *);
void reply_to_sender(int sock_id, struct sockaddr *);

int main(int argc, char **argv) {
    if (argc != 2) {
        oops("Usage:");
    }

    int sock_id, msg_len;
    struct sockaddr addr;
    char buf[BUFSIZ];
    socklen_t addrlen;

    sock_id = make_dgram_server_socket(argv[1]);
    if (sock_id == -1) {
        oops("error");
    }

    addrlen = sizeof(addr);

    while((msg_len = recvfrom(sock_id, buf, BUFSIZ, 0, &addr, &addrlen))) {
        buf[msg_len] = '\0';
        printf("dgrecv: get a message: %s\n", buf);
        say_who_called(&addr);
        reply_to_sender(sock_id, &addr);
    }



}


void say_who_called(struct sockaddr * addr) {
    int c;
    char host[BUFSIZ], port[BUFSIZ];
    c = getnameinfo(addr, sizeof(*addr), host, BUFSIZ, port, BUFSIZ, NI_DGRAM);
    printf("from is %s:%s\n", host, port);
}


void reply_to_sender(int sock_id, struct sockaddr * addr) {
    puts("sock");
    int len = sizeof(*addr);
    char buf[BUFSIZ] = "thanks for sending message";
    sendto(sock_id, buf, strlen(buf), 0, addr, len);
    puts("already send");
}