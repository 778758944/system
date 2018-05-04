#include "./bounce.h"

struct ppball ball;
void ball_move(int);

int main() {

    int c;
    signal(SIGALRM, ball_move);
    set_up(&ball);
    while((c = getchar()) != 'Q') {
        if (c == 'f') ball.x_ttm--;
        if (c == 's') ball.x_ttm++;
        if (c == 'F') ball.y_ttm--;
        if (c == 'S') ball.y_ttm++;
    }

    wrap_up();
    return 0;

}


void ball_move(int signal) {
    int x_cur, y_cur, isMoved;
    x_cur = ball.x_pos;
    y_cur = ball.y_pos;

    if (ball.y_ttm > 0 && ball.y_ttg-- == 1) {
        isMoved = 1;
        ball.y_ttg = ball.y_ttm;
        ball.y_pos += ball.y_dir;
    }

    if (ball.x_ttm > 0 && ball.x_ttg-- == 1) {
        isMoved = 1;
        ball.x_pos += ball.x_dir;
        ball.x_ttg = ball.x_ttm;
    }

    if (isMoved) {
        mvaddch(x_cur, y_cur, BLANK);
        mvaddch(ball.x_pos, ball.y_pos, ball.symbol);
        bounce_or_lose(&ball);
        move(LINES-1, 0);
        refresh();
    }
}