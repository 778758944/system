#include <errno.h>
#include <stdio.h>
extern int errno;
int main() {
    FILE* fp;
    if ((fp = fopen("./aaaa", "r")) == NULL) {
        if (errno == ENOENT) {
            printf("no such file");
        }
    }
    perror("Cannot open file");
    return 0;
}