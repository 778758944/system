#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
int main() {
    int pid, fd;
    pid = fork();

    if (pid == 0) {
        close(1);
        fd = open("./userlist2", O_APPEND | O_RDWR);
        execlp("who", "who", NULL);
    } else {
        wait(NULL);
        puts("done");
    }
    return 0;
}