#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
/*异步就是通过信号机制来出发*/

void handle_input();
void enable_keyboard_signal();
int main() {
    char c;
    enable_keyboard_signal();
    signal(SIGIO, handle_input);
    while(1) {
    }
}

void handle_input(int s) {
    char str[100];
    read(0, str, 100);
    printf("input: %s\n", str);
}

void enable_keyboard_signal() {
    int fd_flags;
    fcntl(0, F_SETOWN, getpid());
    fd_flags = fcntl(0, F_GETFL);
    fcntl(0, F_SETFL, (fd_flags | O_ASYNC));
}