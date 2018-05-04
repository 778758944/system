#include <stdio.h>
#include <stdlib.h>
#define BUFFERSIZE 100

int main(int argc, char** argv) {
    if (argc < 3) {
        puts("Userage: cp1 source target");
        exit(1);
    }

    char* source = argv[1];
    char* target = argv[2];

    FILE * source_fp;
    FILE * target_fp;

    int readsize;

    char* buff = (char*) malloc(sizeof(char) * BUFFERSIZE);

    if ((source_fp = fopen(source, "r")) == NULL) {
        printf("failed to read %s\n", source);
        exit(1);
    }

    if ((target_fp = fopen(target, "w")) == NULL) {
        printf("failed to read %s\n", target);
        exit(1);
    }

    while ((readsize = (int) fread(buff, 1, BUFFERSIZE, source_fp)) > 0) {
        fwrite(buff, 1, readsize, target_fp);
    }

    free(buff);
    fclose(target_fp);
    fclose(source_fp);
    return 0;

}