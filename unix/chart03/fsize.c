#include <stdio.h>
#include <sys/stat.h>

int main() {
    struct stat* data;

    if (stat("./ls.c", data) == 0) {
        printf("size is %lld", data->st_size);
    }
    return 0;
}