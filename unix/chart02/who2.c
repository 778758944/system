#include <time.h>
#include "./utmplib.h"

void showInfo(struct utmp*);

int main() {
    utmp_open();
    struct utmp * p;
    while((p = utmp_next()) != NULL) {
        showInfo(p);
    }

    utmp_close();
    return 0;
}

void showInfo(struct utmp * p) {
    if (p->ut_type == USER_PROCESS) {
        char* timeStr;
        const long timsstamp = (long) p->ut_time;
        timeStr = ctime(&timsstamp);
        printf("%s   %s   %s\n", p->ut_name, p->ut_line, timeStr);
    }
}
