#include "./dgram.h"

int make_dgram_server_socket(char * portnum) {
    struct addrinfo *result, dint;
    int sock_id, rc;

    memset(&dint, 0, sizeof(dint));
    dint.ai_family = AF_INET;
    dint.ai_socktype = SOCK_DGRAM;

    rc = getaddrinfo(NULL, portnum, &dint, &result);

    if (rc != 0) {
        return -1;
    }

    sock_id = socket(PF_INET, result->ai_socktype, result->ai_protocol);

    if (sock_id == -1) {
        return -1;
    }

    if(bind(sock_id, result->ai_addr, result->ai_addrlen) != 0) {
        return -1;
    }

    return sock_id;

}

int make_dgram_client_socket() {
    return socket(PF_INET, SOCK_DGRAM, 0);
}

