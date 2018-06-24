#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE * fp;
    char line[BUFSIZ];
    int pid = getpid();
    char pidstr[BUFSIZ];

    sprintf(pidstr, "%d", pid);
    printf("pis is %d\n", pid);
    

    fp = popen("ps", "r");

    while (fgets(line, BUFSIZ, fp) != NULL) {
        if (strstr(line, pidstr) != NULL) {
            printf("%s\n", line);
        }
    }

    return 0;
}