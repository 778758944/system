#ifndef _UTMPLLIB
#define _UTMPLLIB
#include <utmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <utmp.h>
#define MAXSIZE 6
#define USIZE (sizeof(struct utmp))
void utmp_open();
struct utmp * utmp_next();
int utmp_relaod();
void utmp_close();

#endif