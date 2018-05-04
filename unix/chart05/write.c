#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
int main(int argc, char** argv) {
    if (argc == 1) {
        puts("please enter file to use");
        exit(1);
    }

    FILE* fp;
    char text[100];
    // char enter[] = "\n";
    if ((fp = fopen(argv[1], "w+")) == NULL) {
        perror("error:");
        exit(1);
    }

    puts("enter:");
    while (gets(text) && text[0] != '\0') {
        fprintf(fp, "%c", '\n');
        fprintf(fp, "%s", text);
    }

    return 0;




}