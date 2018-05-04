#include "./util.h"
void show_stat_info(char * file) {
    struct stat filedata;
    char mode_text[15];
    if (stat(file, &filedata) == -1) {
        perror("error:");
    }

    mode_to_letter(filedata.st_mode, mode_text);

    long mtime = (long) filedata.st_mtime;

    printf("%-20s", mode_text);
    printf("%-4lu", filedata.st_nlink);
    printf("%-16s", uid_to_name(filedata.st_uid));
    printf("%-16s", gid_to_name(filedata.st_gid));
    printf("%-8ld", filedata.st_size);
    printf("%.12s", ctime(&mtime));
    printf("%20s\n", file);
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