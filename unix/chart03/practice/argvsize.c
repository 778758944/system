#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    printf("argv[1] = %p\n", argv[1]);
    printf("argv[2] = %p\n", argv[2]);

    strcat(argv[1], "helloworld");
    printf("argv[1] = %s\n", argv[1]);
    printf("argv[2] = %s\n", argv[2]);
    return 0;
}