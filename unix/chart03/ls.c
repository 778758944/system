#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>
void do_ls(char *);
void readstat(char * filename);
int main(int argc, char** argv) {
    if (argc == 1) {
        do_ls(".");
    } else {
        do_ls(argv[1]);
    }
    return 0;
}

void do_ls(char * path) {
    DIR* dirp;
    struct dirent* rec;
    if ((dirp = opendir(path)) == NULL) {
        perror("failed to open");
        exit(1);
    }

    while((rec = readdir(dirp)) != NULL) {
        printf("%s\n", rec->d_name);
    }

    closedir(dirp);
}

void readstat(char * filename) {
    struct stat buf;
    if (stat(filename, &buf) == -1) {
        exit(1);
    }
}