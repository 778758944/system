#include <stdio.h>
#include <stdlib.h>
#include "./popen.h"
#define BUFSIZE 100

int main() {
    FILE * fp;
    int i = 0;
    char buf[BUFSIZE];

    if ((fp = popen("who", "r")) == NULL) {
        perror("error:");
        exit(1);
    }

    while(fgets(buf, BUFSIZE, fp) == NULL) {
        printf("%d. %s", i++, buf);
    }

    puts("done");

    pclose(fp);
    return 0;
}