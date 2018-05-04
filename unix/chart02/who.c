#include <utmp.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

void showInfo(struct utmp);

int main() {
    struct utmp data;
    int file;
    int size = sizeof(data);

    if ((file = open(_PATH_UTMP, O_RDONLY)) == -1) {
        exit(1);
    }

    while(read(file, &data, size) == size) {
        showInfo(data);
    }

    close(file);
    return 0;
}

void showInfo(struct utmp data) {
    if (data.ut_type == USER_PROCESS) {
        long time = (long) data.ut_time;
        printf("%s  %s  %s\n", data.ut_name, data.ut_line, ctime(&time)+4);
    }
}















