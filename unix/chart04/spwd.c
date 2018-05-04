#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#define SIZE 200

ino_t get_inode(char *);
void printpathto(ino_t);
void inum_to_name(ino_t, char*);

int main(){
    char path[SIZE];
    printpathto(get_inode("."));
    putchar('\n');
    return 0;
}

ino_t get_inode(char * p) {
    struct stat inode;
    if (stat(p, &inode) == -1) {
        perror("error:");
        exit(1);
    }
    return inode.st_ino;
}

void inum_to_name(ino_t inode, char * path) {
    DIR *cur_dir;
    struct dirent *cur_dirent;

    if ((cur_dir = opendir(".")) == NULL) {
        perror("error:");
        exit(1);
    }

    while ((cur_dirent = readdir(cur_dir)) != NULL) {
        if (cur_dirent->d_ino == inode) {
            strncpy(path, cur_dirent->d_name, SIZE);
            path[SIZE-1] = '\0';
            closedir(cur_dir);
            return;
        }
    }

    printf("can not find inode\n");
    exit(1);
}

void printpathto(ino_t inode) {
    char path[SIZE];
    if (get_inode("..") != inode) {
        chdir("..");
        inum_to_name(inode, path);
        printpathto(get_inode("."));
        printf("/%s", path);
    }
}

