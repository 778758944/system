#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "../socketlib.h"


int main(int argc, char **argv) {
    char buf[BUFSIZ];
    int readc;
    // close(0);
    int sock_id = connect_to_server(argv[1], argv[2]);
    int pd[2];
    FILE * fp = fdopen(sock_id, "r");

    // dup2(pd[0], sock_id);
    // while ((readc = read(sock_id, buf, BUFSIZ)) > 0) {
        // dup2(0, sock_id);
    // }

    // close(0);

    int fd = open("./girl.jpg", O_CREAT | O_RDWR | O_APPEND, 0777);
    // dup2(fd, 1);

    // printf("fd is %d\n", fd);

    

    while (fgets(buf, BUFSIZ, fp)) {
        // write(fd, buf, readc);
        puts(buf);
    }

    // dup2(0, sock_id);
    close(sock_id);
    return 0;
}