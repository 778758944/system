/*
protocol:
client: HELLO mypid
server: TICK ticketid FAIL no ticket
client: GBYE ticketid
server: THNX message
*/
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "./dgram.h"
#define oops(m) {perror(m); exit(1);}
#define MAXSIZE 3

char res[BUFSIZ];
int handle_request(char *, struct sockaddr *, socklen_t);
void do_sendticket();
void do_recycle();
int tickets[MAXSIZE] = {0, 0, 0};
int occupy_num = 0;
int sock_id;
int main(int argc, char **argv) {
    if (argc != 2) {
        oops("Usage:");
    }

    int read_len; 
    socklen_t addrlen;
    struct sockaddr addr;
    char buf[BUFSIZ];
    addrlen = sizeof(struct sockaddr);
    sock_id = make_dgram_server_socket(argv[1]);
    if (sock_id == -1) {
        oops("socket");
    }
    
    while ((read_len = recvfrom(sock_id, buf, BUFSIZ, 0, &addr, &addrlen)) > 0) {
        handle_request(buf, &addr, addrlen);
    }
   
    // handle_request(buf, &addr, addrlen);

    return 0;
}

int handle_request(char * str, struct sockaddr * addr, socklen_t len) {
    printf("%s\n", str);
    if (strncmp(str, "HELLO", 5) == 0) {
        do_sendticket(str+6);
    } else if (strncmp(str, "GBYE", 4) == 0) {
        do_recycle(str+5);
    } else {
        oops("do not have that option");
    }

    sendto(sock_id, res, BUFSIZ, 0, addr, len);
    return 0;
}

void do_sendticket(char * str) {
    puts("get ticket");
    int pid, x;
    sscanf(str, "%d", &pid);
    if (occupy_num == MAXSIZE) {
        sprintf(res, "FAIL no ticket");
    } else {
        for(x = 0; x < MAXSIZE && tickets[x] != 0 ; x++) {
            continue;
        }

        tickets[x] = pid;

        sprintf(res, "TICK %d .%d", pid, x);
        occupy_num++;
    }
}


void do_recycle(char * str) {
    puts("release ticket");
    int x;
    char * cp;
    if ((cp = strchr(str, '.')) == NULL) {
        oops("error:");
    }
    sscanf(cp+1, "%d", &x);
    sprintf(res, "THNX message");
    tickets[x] = 0;
    occupy_num--;
}

