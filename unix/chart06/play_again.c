#include <stdio.h>
#include <termios.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#define QUESTION "Do you want another transcation(y/n)"
#define SLEEP 2
#define TRIES 3
#define BEEP putchar('\a')

int get_response(char *, int times);
void tty_mode(int);
void set_tty();
void set_nodelay_mode();
char get_ok_char();
void handle_signal(int);

int main() {
    int response;
    tty_mode(0);
    set_tty();
    set_nodelay_mode();
    signal(SIGINT, handle_signal);
    response = get_response(QUESTION, TRIES);
    tty_mode(1);
    return response;
}

int get_response(char * q, int times) {
    printf("%s", q);
    fflush(stdout);
    char input;
    while (1) {
        sleep(SLEEP);
        input = tolower(get_ok_char());
        if (input == 'y') {
            return 0;
        } 

        if (input == 'n') {
            return 1;
        }

        if (times-- == 0) {
            return 2;
        }
        BEEP;
    }
}

void set_tty() {
    struct termios ttyinfo;
    tcgetattr(0, &ttyinfo);

    ttyinfo.c_lflag &= ~ICANON; /*取消缓冲区*/
    ttyinfo.c_cc[VMIN] = 1; /*get 1 char one time*/
    ttyinfo.c_lflag &= ~ECHO; /*关闭回显示*/
    tcsetattr(0, TCSANOW, &ttyinfo);
}

void tty_mode(int a) {
    static struct termios ttyinfo;
    static int original_flags;
    if (a == 0) {
        tcgetattr(0, &ttyinfo);
        original_flags = fcntl(0, F_GETFL);
    } else {
        tcsetattr(0, TCSANOW, &ttyinfo);
        fcntl(0, F_SETFL, original_flags);
    }
}

void set_nodelay_mode() {
    int f_flags = fcntl(0, F_GETFL);
    f_flags |= O_NDELAY;
    fcntl(0, F_SETFL, f_flags);
}

char get_ok_char() {
    char c;
    while ((c = getchar()) != EOF && strchr("yYnN", c) == NULL) {
        continue;
    }

    return c;

}

void handle_signal(int signum) {
    tty_mode(1);
    exit(1);
}

