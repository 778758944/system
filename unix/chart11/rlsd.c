#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <errno.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#define PORT "13001"
#define oops(m) {perror(m); exit(1);}

int main() {
    struct addrinfo * result, hint;
    int rc, sock_id, sock_fp;
    char dirname[BUFSIZ], command[BUFSIZ];
    int read_rc;
    FILE * pfp, *sock_fpo;
    char c;

    memset(&hint, 0, sizeof(hint));
    hint.ai_family = AF_INET;
    hint.ai_socktype = SOCK_STREAM;
    rc = getaddrinfo(NULL, PORT, &hint, &result);
    if (rc == -1) {
        oops(gai_strerror(rc));
    }

    sock_id = socket(PF_INET, result->ai_socktype, result->ai_protocol);

    if (bind(sock_id, result->ai_addr, result->ai_addrlen) != 0) {
        oops("bind");
    }

    if (listen(sock_id, 1) != 0) {
        oops("listen");
    }

    while(1) {
        if ((sock_fp = accept(sock_id, NULL, NULL)) == -1) {
            oops("accept");
        }

        if ((read_rc = read(sock_fp, dirname, BUFSIZ-5)) == -1) {
            oops("error:");
        }

        puts(dirname);

        sprintf(command, "ls %s", dirname);
        if ((pfp = popen(command, "r")) == NULL) {
            oops("popen error");
        }

        if ((sock_fpo = fdopen(sock_fp, "w")) == NULL) {
            oops("fdopen error");
        }

        

        while((c = getc(pfp)) != EOF) {
            putc(c, sock_fpo);
        }

        pclose(pfp);
        fclose(sock_fpo);
        
    }


}
