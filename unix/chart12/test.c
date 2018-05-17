#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv) {
    FILE * fp;
    char c;
    int fileLen;
    int i;

    if ((fp = fopen(argv[1], "r")) == NULL) {
        puts("error");
        exit(2);
    }

    fseek(fp, 0, SEEK_END);
    fileLen = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    printf("fileLen %d\n", fileLen);

    for(i = 0; i < fileLen; i++) {
        putchar(getc(fp));
    }
    

    return 0;
    
}