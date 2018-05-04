#include <stdio.h>
int main(int argc, char **argv) {
    int i;
    printf("argv count: %d\n", argc);
    for(i = 0; i < argc; i++) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }

    fprintf(stderr, "this message is send to stderr\n");
}