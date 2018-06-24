#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define oops(m) {perror(m); exit(1);}
void goDir();

int main() {
    goDir();
    printf("\n");
    return 0;   
}

void goDir() {
    struct stat currentInfo;
    struct dirent * dirinfo;
    DIR * p;
    if (stat(".", &currentInfo) != 0) {
        oops("stat:");
    }

    if ((p = opendir("..")) == NULL) {
        oops("opendir:");
    }

    while ((dirinfo = readdir(p)) != NULL) {
        if (strcmp(dirinfo->d_name, ".") == 0) {
            if (dirinfo->d_ino != currentInfo.st_ino) {
                chdir("..");
                goDir();
            }
        } else {
            if (dirinfo->d_ino == currentInfo.st_ino) {
                printf("/%s", dirinfo->d_name);
            }
        }
    }
}





