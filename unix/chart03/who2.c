#include "./util.h"
#include <dirent.h>
void do_ls(char *);
int main(int argc, char** argv) {
    if (argc == 1) {
        do_ls(".");
    } else {
        do_ls(argv[1]);
    }

    return 0;
}

void do_ls(char * d) {
    DIR * dirp;
    struct dirent * filedata;

    if ((dirp = opendir(d)) == NULL) {
        perror("error:");
    }

    while((filedata = readdir(dirp)) != NULL) {
        show_stat_info(filedata->d_name);
    }

    closedir(dirp);
}

