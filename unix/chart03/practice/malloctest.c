#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {
    /*
    char * p1 = (char *) malloc(BUFSIZ);
    strcat(p1, "test");
    free(p1);
    char * p2 = (char *) malloc(BUFSIZ);
    memset(p2, 0, BUFSIZ);
    printf("p2 is %s\n", p2);
    */
    int i = 0;
    while(i < 10) {
        char buf[BUFSIZ];
        strcat(buf, "test/");
        printf("buf is %s\n", buf);
        printf("buf is %p\n", buf);
        i++;
    }
    return 0;
}