#include <stdio.h>
#include <curses.h>
#include <unistd.h>
#define ROW 10
#define LEFTEDGE 10
#define RIGHTEDGE 30
int main() {
    char * message = "hello, world";
    char * blank = "               ";
    int pos = 10;
    int dir = 1;
    initscr();
    clear();
    while(1) {
        move(ROW, pos);
        addstr(message);
        move(LINES-1, COLS-1);
        sleep(1);
        refresh();
        move(ROW, pos);
        addstr(blank);
        pos += dir;
        if (pos >= RIGHTEDGE) {
            dir = -1;
        } else if (pos <= LEFTEDGE) {
            dir = 1;
        }
    }
    return 0;
}