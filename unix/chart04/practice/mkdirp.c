#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#define oops(m) {perror(m); exit(1);}

void createDir(char * path);
int main(int argc, char **argv) {
    if (argc < 2) {
        oops("error:");
    }

    createDir(argv[1]);
    return 0;  
}

/*
./ form current
/  from root
   from current
*/

void createDir(char * path) {
    char * p;
    int i;
    char * fullpath = path;

    while ((p = strchr(fullpath, '/')) != NULL) {
        char newdir[BUFSIZ];
        i = p - path;
        if (i > 1) {
            memset(newdir, 0, BUFSIZ);
            strncpy(newdir, path, i);
            printf("new dir is %s\n", newdir);
            mkdir(newdir, S_IRWXU | S_IRWXG | S_IRWXO);
        }
        fullpath = p + 1;
    }

    mkdir(path, S_IRWXU | S_IRWXG | S_IRWXO);
    
}