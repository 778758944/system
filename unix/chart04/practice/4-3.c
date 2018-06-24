#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <string.h>

#define oops(m) {perror(m); exit(1);}

bool isdir(char * path) {
    struct stat info;
    if (stat(path, &info) == 0) {
        return S_ISDIR(info.st_mode);
    }
    return false;
}


int main(int argc, char **argv) {
    if (argc < 3) {
        oops("Usage: rename2 file path");
    }

    if (isdir(argv[2])) {
        char * filename;
        char dest[BUFSIZ];
        if ((filename = strrchr(argv[1], '/')) == NULL) {
            filename = argv[1];
        } else {
            filename += 1;
        }
        printf("filename %s\n", filename);
        strcat(dest, argv[2]);
        strcat(dest, "/");
        strcat(dest, filename);
        printf("dest %s\n", dest);
        rename(argv[1], dest);
    } else {
        rename(argv[1], argv[2]);
    }

    return 0;




}
