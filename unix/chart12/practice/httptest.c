#include <stdio.h>
#include <string.h>
#include "../socketlib.h"

int main(int argc, char **argv) {
    int sock_id, fd;
    sock_id = make_server_socket(argv[1]);
    char buf[BUFSIZ];
    FILE * fp;

    while (1) {
        fd = accept(sock_id, NULL, NULL);
        fp = fdopen(fd, "r");
        while(fgets(buf, BUFSIZ, fp) != NULL && strcmp("\r\n", buf) != 0) {
            puts(buf);
        }
        //read body
        while(fgets(buf, BUFSIZ, fp) != NULL) {
            puts(buf);
        }
    }

    puts("done");

}