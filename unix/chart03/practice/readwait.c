#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main() {
    FILE * fp;
    fp = fopen("./a", "r");
    char c;

    while((c = getc(fp)) != EOF) {
        printf("%c\n", c);
        sleep(20);
    }

    return 0;
}