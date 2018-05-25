#include <stdio.h>
#include <unistd.h>

int main() {
    char str[BUFSIZ];
    read(0, str, BUFSIZ);
    printf("data is %s\n", str);
    return 0;
}