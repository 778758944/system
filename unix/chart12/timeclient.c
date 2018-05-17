#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "./socketlib.h"
#define oops(m) {perror(m); exit(1);}

int main(int argc, char **argv) {
    if (argc != 3) {
        oops("Usage:");
    }

    int sock, read_c;
    char buf[BUFSIZ];
    

    sock = connect_to_server(argv[1], argv[2]);

    if (sock == -1) {
        oops("error");
    }

    if ((read_c = read(sock, buf, BUFSIZ)) > 0) {
        write(1, buf, read_c);
    }

    return 0;
    
}