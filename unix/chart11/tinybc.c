#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

#define oops(m, x) {perror(m); exit(x);}
#define BUFSIZE 100

void be_dc(int in[2], int out[2]);
void be_bc(int todc[2], int fromdc[2]);

int main() {
    int todc[2], fromdc[2], pid;

    if (pipe(todc) == -1 || pipe(fromdc) == -1) {
        oops("error to pipe", 1);
    }

    if ((pid = fork()) == -1) {
        oops("error to fork", 1);
    }

    if (pid == 0) {
        be_dc(todc, fromdc);
    } else {
        be_bc(todc, fromdc);
        wait(NULL);
    }
    

    return 0;
}


void be_dc(int in[2], int out[2]) {
    if (dup2(in[0], 0) == -1) {
        oops("error to redirect", 1);
    }

    close(in[0]);
    close(in[1]);


    if (dup2(out[1], 1) == -1) {
        oops("error to redirect", 1);
    }

    close(out[0]);
    close(out[1]);

    execlp("dc", "dc", "-", NULL);
    oops("can not run dc", 1);
}

void be_bc(int todc[2], int fromdc[2]) {
    int num1, num2;
    char operation[BUFSIZ], message[BUFSIZE];
    FILE * fpout, * fpin;
    fpout = fdopen(todc[1], "w");
    fpin = fdopen(fromdc[0], "r");

    while(printf("tinydc:"), fgets(message, BUFSIZE, stdin)) {
        if (sscanf(message, "%d%[+-*/^]%d", &num1, operation, &num2) != 3) {
            printf("enter error");
            continue;
        }

        if (fprintf(fpout, "%d\n%d\n%c\np\n", num1, num2, *operation) == EOF) {
            oops("error writing", 1);
        }

        fflush(fpout);
        if (fgets(message, BUFSIZE, fpin) == NULL) {
            break;
        }
        printf("%d %c %d = %s", num1, *operation, num2, message);
    }
    fclose(fpout);
    fclose(fpin);
}





