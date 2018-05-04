#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#define SIZE 300
#define oops(m) {perror(m); exit(1);}

int main(int argc, char ** argv) {
    struct addrinfo *result, hint;
    int rc, sock_id;
    char * port = "13001";
    char res[SIZE];
    int n_read;
    if (argc != 3) {
        oops("Usage error:");
    }
    memset(&hint, 0, sizeof(hint));
    hint.ai_family = AF_INET;
    hint.ai_socktype = SOCK_STREAM;


    rc = getaddrinfo(argv[1], port, &hint, &result);

    if (rc != 0) {
        oops(gai_strerror(rc));
    }

    /*apply sock*/
    sock_id = socket(PF_INET, result->ai_socktype, result->ai_protocol);
    if (sock_id == -1) {
        oops("create sock error");
    }

    if (connect(sock_id, result->ai_addr, result->ai_addrlen) == -1) {
        oops("connect error");
    }

    if (write(sock_id, argv[2], strlen(argv[2])) == -1) {
        oops("write error");
    }

    if (write(sock_id, "\n", 1) == -1) {
        oops("write error");
    }

    while ((n_read = read(sock_id, res, SIZE)) > 0) {
        printf("n_read %d\n", n_read);
        if (write(1, res, n_read) == -1) {
            oops("write error");
        }
    }

    close(sock_id);

    return 0;
}

