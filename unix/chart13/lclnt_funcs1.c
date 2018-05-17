#include "./lclnt_funcs1.h"
#include "./dgram.h"


static int socket_id;
static struct addrinfo * result;
static int pid;
static char res[BUFSIZ];
static char ticket[BUFSIZ];

int do_transcation(char * msg) {
    puts("send request");
    int sendstatus, readstatus;
    sendstatus = sendto(socket_id, msg, strlen(msg), 0, result->ai_addr, result->ai_addrlen);
    if (sendstatus == -1) {
        return -1;
    }

    readstatus = recvfrom(socket_id, res, BUFSIZ, 0, NULL, 0);

    if (readstatus == -1) {
        return -1;
    }

    return 0;
}


int setup(char * hostname, char * portnum) {
    int rc;
    struct addrinfo dint;
    memset(&dint, 0, sizeof(dint));
    dint.ai_socktype = SOCK_DGRAM;
    dint.ai_family = AF_INET;
    rc = getaddrinfo(hostname, portnum, &dint, &result);
    if (rc != 0) {
        return -1;
    }

    socket_id = make_dgram_client_socket();
    if (socket_id == -1) {
        return -1;
    }

    pid = getpid();

    return 0;
}


int get_ticket() {
    char sendMsg[BUFSIZ];
    int sendstatus;
    int read_len;
    sprintf(sendMsg, "HELLO %d", pid);
    if (do_transcation(sendMsg) == -1) {
        return -1;
    }

    if(strncmp(res, "TICK", 4) == 0) {
        return 0;
    } else {
        return -1;
    }
}


int release_ticket() {
    char sendMsg[BUFSIZ];
    sprintf(sendMsg, "GBYE %s", res+5);

    if (do_transcation(sendMsg) == -1) {
        return -1;
    } 

    if (strncmp(res, "THNX", 4) == 0) {
        printf("message %s\n", res + 5);
        return 0;
    } else {
        return -1;
    }
}
