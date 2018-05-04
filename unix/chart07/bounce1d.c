#include <stdio.h>
#include <sys/time.h>
#include <curses.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <aio.h>
#include <errno.h>

#define MESSAGE "hello"
#define BLANK "      "

int col = 0, row = 10, dir = 1;
int done = 0;
struct aiocb kbcbuf;



int set_timer(int time);
void move_msg(int signum);
void on_input(int signum);
void enable_kbd_signals();
void recovery();
void on_async_input(int);
void setup_aio_buffer();

int main() {
    char c;
    int delay = 200;
    initscr();
    clear();
    recovery();
    signal(SIGALRM, move_msg);
    signal(SIGIO, on_input);
    // enable_kbd_signals();
    setup_aio_buffer();
    aio_read(&kbcbuf);
    move(row, col);
    addstr(MESSAGE);
    set_timer(200);
    while(!done) {
        pause(); // 挂起进程
        // c = getch();
        // if (c == 'Q') break;
        // if (c == ' ') dir = -dir;
        // if (c == 'f') delay = delay/2;
        // if (c == 'g') delay = delay * 2;
        // set_timer(delay);
    }
    endwin();
    // recovery();
    return 0;
}




void move_msg(int signum) {
    move(row, col);
    addstr(BLANK);
    col += dir;
    move(row, col);
    addstr(MESSAGE);
    move(LINES-1, 0);
    refresh();
    if (dir == -1 && col <= 0) {
        dir = 1;
    } else if (dir == 1 && col + strlen(MESSAGE) >= COLS) {
        dir = -1;
    }
}

int set_timer(int time) {
    struct itimerval new_time;
    long sec, nsec;
    sec = time/1000;
    nsec = (time % 1000) * 1000L;
    new_time.it_value.tv_sec = sec;
    new_time.it_value.tv_usec = nsec;

    new_time.it_interval.tv_sec = sec;
    new_time.it_interval.tv_usec = nsec;

    return setitimer(ITIMER_REAL, &new_time, NULL);
}

void on_input(int signum) {
    char c = getch();

    if (c == 'Q' || c == EOF) {
        done = 1;
    } else if (c == ' ') {
        dir = -dir;
    }
}

void on_async_input(int signum) {
    char c;
    char * cp = (char *) kbcbuf.aio_buf;

    if (aio_error(&kbcbuf) != 0) {
        perror("reading failed");
    } else {
        if (aio_return(&kbcbuf) == 1) {
            c = *cp;
            if (c == 'Q' || c == EOF) {
                done = 1;
            } else if (c == ' ') {
                dir = -dir;
            }
        }
    }
    // new read request
    aio_read(&kbcbuf);
}

void enable_kbd_signals() {
    int fd_flags;
    fcntl(0, F_SETOWN, getpid()); // kenerl will send signal when press a key
    fd_flags = fcntl(0, F_GETFL);
    fcntl(0, F_SETFL, fd_flags|O_ASYNC);
}

void recovery() {
    static int fd_flags;

    if(fd_flags) {
        fcntl(0, F_SETFL, fd_flags);
    } else {
        fcntl(0, F_GETFL);
    }
}

void setup_aio_buffer() {
    static char input[1];

    /*describe what to read*/
    kbcbuf.aio_fildes = 0; /*file describe*/
    kbcbuf.aio_buf = input;
    kbcbuf.aio_nbytes = 1; /*byte to read*/
    kbcbuf.aio_offset = 0; /*offset in file*/

    kbcbuf.aio_sigevent.sigev_notify = SIGEV_SIGNAL;
    kbcbuf.aio_sigevent.sigev_signo = SIGIO;
}

