#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
void show_stat_info(char *);
void mode_to_letter(int mode, char * str);
char * uid_to_name(uid_t uid);
char * gid_to_name(gid_t gid);
int main(int argc, char** argv) {
    if (argc > 1) {
        show_stat_info(argv[1]);
    } else {
        perror(argv[1]);
    }

    return 0;
}

void show_stat_info(char * file) {
    struct stat filedata;
    char mode_text[15];
    if (stat(file, &filedata) == -1) {
        perror("error:");
    }

    mode_to_letter(filedata.st_mode, mode_text);

    long mtime = (long) filedata.st_mtime;

    printf("mode: %s\n", mode_text);
    printf("links: %lu\n", filedata.st_nlink);
    printf("user: %s\n", uid_to_name(filedata.st_uid));
    printf("group: %s\n", gid_to_name(filedata.st_gid));
    printf("size: %ld\n", filedata.st_size);
    printf("mtime: %s", ctime(&mtime));
    printf("filename: %s\n", file);
}

void mode_to_letter(int mode, char * str) {
    strcpy(str, "----------");

    if (S_ISDIR(mode)) str[0] = 'd';
    if (S_ISCHR(mode)) str[0] = 'c';
    if (S_ISBLK(mode)) str[0] = 'b';

    if (mode & S_IRUSR) str[1] = 'r';
    if (mode & S_IWUSR) str[2] = 'w';
    if (mode & S_IXUSR) str[3] = 'x';

    if (mode & S_IRGRP) str[4] = 'r';
    if (mode & S_IWGRP) str[5] = 'w';
    if (mode & S_IXGRP) str[6] = 'x';

    if (mode & S_IROTH) str[7] = 'r';
    if (mode & S_IWOTH) str[8] = 'w';
    if (mode & S_IXOTH) str[9] = 'x';
}

char * uid_to_name(uid_t uid) {
    return getpwuid(uid)->pw_name;
}

char * gid_to_name(gid_t gid) {
    return getgrgid(gid)->gr_name;
}





