#include "./bounce.h"


int set_timer(int delay) {
    struct itimerval new_time;
    long sec, nsec;
    sec = delay/1000;
    nsec = (delay % 1000) * 1000L;
    new_time.it_value.tv_sec = sec;
    new_time.it_value.tv_usec = nsec;

    new_time.it_interval.tv_sec = sec;
    new_time.it_interval.tv_usec = nsec;

    return setitimer(ITIMER_REAL, &new_time, NULL);
}

void set_up(struct ppball *ball) {
    initscr();
    clear();
    noecho();
    crmode();
    ball->y_pos = Y_INIT;
    ball->x_pos = X_INIT;
    ball->x_ttm = ball->x_ttg = X_TTM;
    ball->y_ttm = ball->y_ttg = Y_TTM;
    ball->y_dir = 1;
    ball->x_dir = 1;
    ball->symbol = DFL_SYMBOL;

    mvaddch(ball->x_pos, ball->y_pos, ball->symbol);

    refresh();
    set_timer(1000/TICKS_PER_SEC);
}

void bounce_or_lose(struct ppball *ball) {
    if (ball->x_pos == TOP_ROM) {
        ball->x_dir = 1;
    } else if (ball->x_pos == BOT_ROM) {
        ball->x_dir = -1;
    }
    
    if (ball->y_pos == LEFT_EDGE) {
        ball->y_dir = 1;
    } else if (ball->y_pos == RIGHT_EDGE) {
        ball->y_dir = -1;
    }
}

void wrap_up() {
    set_timer(0);
    endwin();
}