#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <string.h>
#include <dirent.h>
#define oops(m) {perror(m); exit(1);}

bool isdir(char * path);
void writeToDir(char * filename, char * dirpath);
char * getSourceFile(DIR * dirpath);



int main(int argc, char** argv) {
    if (argc != 3) {
        oops("Usage: cp file1 file2");
    }
    FILE *f1, *f2;
    char c;
    char dest[BUFSIZ];
    bool isDestDir;
    bool isSourDir;
    DIR * sourcedir;
    char * sourcefile;
    

    isDestDir = isdir(argv[2]);
    isSourDir = isdir(argv[1]);

    if (isSourDir) {
        sourcedir = opendir(argv[1]);
        while((sourcefile = getSourceFile(sourcedir)) != NULL) {
            printf("sourcefile %s", )
        }
    }
    

    if ((f1 = fopen(argv[1], "r")) == NULL) {
        oops("file open:");
    }

    isDestDir = isdir(argv[2]);


    if (isDestDir) {
        strcpy(dest, argv[2]);
        puts("dir path");
        char *tmp_ptr;
        if ((tmp_ptr = strrchr(argv[1], '/')) == NULL) {
            tmp_ptr = argv[1];
        } else {
            tmp_ptr = tmp_ptr + 1;
        }


        printf("tmp %s\n", tmp_ptr);
        strcat(dest, "/");
        strcat(dest, tmp_ptr);
        printf("argv[2] %s\n", argv[2]);
    }

    if ((f2 = fopen(dest, "w")) == NULL) {
        oops("file open:");
    }

    while ((c = getc(f1)) != EOF) {
        putc(c, f2);
    }

    return 0;

}

bool isdir(char * path) {
    struct stat info;
    stat(path, &info);
    return S_ISDIR(info.st_mode);
}

void writeToDir(char * filename, char * dirpath) {
    char dest[BUFSIZ];


    // dest = dirpath



}

char * getSourceFile(DIR * dirpath) {
    struct dirent * info;
    char * p;
    if ((info = readdir(dirpath)) != NULL) {
        return info->d_name;
    }
    return NULL;
}