#include "./socketlib.h"

int make_server_socket(char *portnum) {
    struct addrinfo *result, dint;
    int sock_id, rc;
    memset(&dint, 0, sizeof(dint));
    dint.ai_socktype = SOCK_STREAM;
    dint.ai_family = AF_INET;

    rc = getaddrinfo(HOSTNAME, portnum, &dint, &result);
    if (rc != 0) {
        return -1;
    }

    sock_id = socket(PF_INET, result->ai_socktype, result->ai_protocol);

    if (sock_id == -1) {
        return -1;
    }

    if (bind(sock_id, result->ai_addr, result->ai_addrlen) == -1) {
        return -1;
    }

    freeaddrinfo(result);

    if (listen(sock_id, 10) == -1) {
        return -1;
    }

    return sock_id;
}

int connect_to_server(char *hostname, char *portnum) {
    struct addrinfo *result, dint;
    int sock_id, rc;

    memset(&dint, 0, sizeof(dint));
    dint.ai_socktype = SOCK_STREAM;
    dint.ai_family = AF_INET;

    rc = getaddrinfo(hostname, portnum, &dint, &result);
    if (rc != 0) {
        return -1;
    }

    sock_id = socket(PF_INET, result->ai_socktype, result->ai_protocol);
    if (sock_id == -1) {
        return -1;
    }

    if (connect(sock_id, result->ai_addr, result->ai_addrlen) == -1) {
        return -1;
    }

    return sock_id;
}