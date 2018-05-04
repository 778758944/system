#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
int main() {
    char path[20][10];
    int i = 0;
    char dname[200];
    DIR * current_dir;
    unsigned long long a = 0;

    struct dirent *current_dirent;
    struct stat info;
    // stat(".", &info);
    // printf("%llu\n", info.st_ino);

    // chdir("..");
    // stat(".", &info);
    // printf("%llu\n", info.st_ino);

    stat(".", &info);
    while (info.st_ino != a) {
        if (chdir("..") == -1) {
            exit(1);
        }

        a = info.st_ino;

        if ((current_dir = opendir(".")) == NULL) {
            exit(1);
        }

        while ((current_dirent = readdir(current_dir)) != NULL) {
            if (current_dirent->d_ino == a) {
                strcpy(path[i], current_dirent->d_name);
                closedir(current_dir);
            }
        }

        stat(".", &info);
        i++;
    }

    printf("%s\n", path);


    return 0;
}
