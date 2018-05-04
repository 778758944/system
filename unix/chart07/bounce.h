#ifndef BOUNCE
#include <stdio.h>
#include <signal.h>
#include <curses.h>
#include <sys/time.h>
#define BOUNCE
#define BLANK ' '
#define DFL_SYMBOL 'O'
#define TOP_ROM 5
#define BOT_ROM 20
#define LEFT_EDGE 10
#define RIGHT_EDGE 50
#define X_INIT 10
#define Y_INIT 10
#define TICKS_PER_SEC 50
#define X_TTM 5
#define Y_TTM 8

struct ppball {
    int y_pos;
    int x_pos;
    int y_ttm;
    int x_ttm;
    int y_ttg;
    int x_ttg;
    int y_dir;
    int x_dir;
    char symbol;
};

int set_timer(int delay);
void set_up(struct ppball *);
// void ball_move(int signal);
void bounce_or_lose(struct ppball*);
void wrap_up();








#endif