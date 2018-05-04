#include <stdio.h>
#include <stdlib.h>
#define PAGELEN 24
#define LINELEN 512
void do_more(FILE * fp);
int see_more(FILE* fp);

int main(int ac, char* argv[]) {
    FILE* fp;
    if (ac == 1){
        do_more(stdin);
    } else {
        if ((fp = fopen(argv[1], "r")) != NULL) {
            do_more(fp);
            fclose(fp);
        }
    }

    return 0;
}

void do_more(FILE* fp) {
    char line[LINELEN];
    int num_of_line = 0;
    FILE* fp_tty;
    if ((fp_tty = fopen("/dev/tty", "r")) == NULL) {
        exit(0);
    }
    int reply;
    while(fgets(line, LINELEN, fp)) {
        if (num_of_line == PAGELEN) {
            reply = see_more(fp_tty);
            if (reply == 0) {
                exit(1);
            }
            num_of_line -= reply;
        }
        if (fputs(line, stdout) == EOF) {
            exit(1);
        }
        num_of_line++;
    }
}

int see_more(FILE* fp) {
    int c;
    printf("--more--");
    while((c = getc(fp)) != EOF) {
        if (c == 'q') {
            return 0;
        } else if (c == ' ') {
            return PAGELEN;
        } else if (c == '\n') {
            return 1;
        }
    }
}