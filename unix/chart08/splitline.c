#include "./splitline.h"


char ** splitline(char * str) {
    /*drop \n*/
    if (str[strlen(str) - 1] == '\n') {
        str[strlen(str) - 1] = '\0';
    }
    char * find;
    char buf[100];

    /*malloc for pointer*/
    char **p = malloc(100 * sizeof(char *));
    int i = 0;

    while((find = strchr(str, BLANK)) != NULL) {
        find += 1;
        int size = find-str;
        if (size > 1 || str[0] != ' ') {
            p[i] = malloc(size);
            strncpy(p[i], str, size);
            p[i][size-1] = '\0';
            i++;
        }
        str = find;
    }

    // printf("str = %d, i = %d\n", str[0], i);
    if (str[0] != '\0') {
        p[i] = (char *) malloc(strlen(str) + 1);
        strcpy(p[i], str);
        // i = i+1;
    }
    return p;
}

void freesplit(char ** p) {
    char ** first = p;
    while (*p) {
        free(*p);
        p += 1;
    }
    free(first);
}