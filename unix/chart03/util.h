#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <sys/types.h>
void show_stat_info(char *);
void mode_to_letter(int mode, char * str);
char * uid_to_name(uid_t uid);
char * gid_to_name(gid_t gid);