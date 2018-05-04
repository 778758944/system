#include <stdio.h>
#include <ncurses.h>

int main() {
    initscr(); // initial curses

    clear();
    move(10, 20);
    addstr("Hello, world");
    move(LINES-1, 0);
    refresh();
    getch(); // wait for user input
    endwin(); // turn off curses
}
