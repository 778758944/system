#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <string.h>


#define oops(m) {perror(m); exit(1);}

void showdir(char * path);
bool isdir(char * path);
char * getFileName(char * path1, char * path2);


int main(int argc, char **argv) {
    if (argc < 2) {
        oops("Usage: lsr path");
    }

    showdir(argv[1]);
    return 0;
}


void showdir(char * path) {
    DIR * p;
    struct dirent * dir ;
    if ((p = opendir(path)) == NULL) {
        oops("readdir");
    }

    while((dir = readdir(p)) != NULL) {
        if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0) {
            char * filename = getFileName(path, dir->d_name);
            // printf("filename %s\n", filename);
            if (isdir(filename)) {
                printf("show dir %s:\n", filename);
                showdir(filename);
            } else {
                printf("%s\n", dir->d_name);
            }
            // printf("%s\n", dir->d_name);
            // free(filename);
        }
    }
}

bool isdir(char * path) {
    struct stat buf;
    if (stat(path, &buf) == 0) {
        return S_ISDIR(buf.st_mode);
    }

    return false;
}

char * getFileName(char * path1, char * path2) {
    // printf("path1 %s\n", path1);
    // printf("path2 %s\n", path2);
    char * name;
    name = (char *) malloc(BUFSIZ);
    strcat(name, path1);
    strcat(name, "/");
    strcat(name, path2);
    // printf("p is %s\n", name);
    return name;
}