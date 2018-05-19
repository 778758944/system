#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdbool.h>

#define oops(m) {perror(m); exit(1);}

char * getSourceFile(DIR * p);
bool isdir(char * path);
void writeFile(char * source, char * destfile);
char * getFileName(char * path1, char * path2);

int main(int argc, char **argv) {
    if(argc < 3) {
        oops("Usage: cp2 file1 file2");
    }

    bool issourcedir, isdestdir;

    issourcedir = isdir(argv[1]);
    isdestdir = isdir(argv[2]);

    if (issourcedir) {
        char * filename;
        DIR * sourcedir;
        sourcedir = opendir(argv[1]);

        while((filename = getSourceFile(sourcedir)) != NULL) {
            printf("source file is %s\n", filename);
            if (strcmp(filename, ".") != 0 && strcmp(filename, "..") != 0) {
                char * sourcefile, *destfile;
                sourcefile = getFileName(argv[1], filename);
                destfile = getFileName(argv[2], filename);
                writeFile(sourcefile, destfile);
                free(sourcefile);
                free(destfile);
            }
        }


        
    }

    return 0;


}

char * getSourceFile(DIR * p) {
    struct dirent * dirinfo;
    if ((dirinfo = readdir(p)) == NULL) {
        return NULL;
    }

    return dirinfo->d_name;
}

bool isdir(char * path) {
    struct stat fileinfo;
    stat(path, &fileinfo);
    return S_ISDIR(fileinfo.st_mode);
}

void writeFile(char * source, char * destfile) {
    printf("s %s, d %s\n", source, destfile);
    FILE * fp1, *fp2;
    char c;
    if ((fp1 = fopen(source, "r")) == NULL) {
        oops("file open:");
    }

    if((fp2 = fopen(destfile, "w")) == NULL) {
        oops("file open:");
    }

    while((c = getc(fp1)) != EOF) {
        putc(c, fp2);
    }

    fclose(fp1);
    fclose(fp2); 
}

char * getFileName(char * path1, char * path2) {
    char * filename;
    filename = (char *) malloc(BUFSIZ);
    strcat(filename, path1);
    strcat(filename, "/");
    strcat(filename, path2);
    return filename;
}


