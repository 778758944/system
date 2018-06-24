#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE * fp;
    fp = fopen("./test", "r");
    char buf[BUFSIZ];

    while(fgets(buf, BUFSIZ, fp) != NULL) {
        puts(buf);
    }

    return 0;
}