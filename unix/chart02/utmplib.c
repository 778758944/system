#include "./utmplib.h"
static struct utmp utmpBuf[MAXSIZE * USIZE];
static int num_of_stores;
static int current_num;
static FILE * fp;

void utmp_open() {
    if ((fp = fopen(_PATH_UTMP, "r")) == NULL) {
        puts("failed to open utmp file");
        exit(1);
    }

    num_of_stores = current_num = 0;
}

struct utmp * utmp_next() {
    if (!fp) {
        return NULL;
    }

    if (num_of_stores == current_num) {
        num_of_stores = utmp_relaod();
        if (num_of_stores == 0) {
            return NULL;
        } else {
            current_num = 1;
            return &utmpBuf[0];
        }
    }
    current_num++;
    return &utmpBuf[current_num - 1];
}

int utmp_relaod() {
    if (fp) {
        int readsize;
        readsize = (int) fread(utmpBuf, USIZE, MAXSIZE, fp);
        return readsize;
    }
    return 0;
}

void utmp_close() {
    fp && fclose(fp);
}
