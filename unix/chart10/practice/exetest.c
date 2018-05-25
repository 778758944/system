#include <stdio.h>
#include <unistd.h>

int main() {
    execlp("cat", "cat", "./sortfile", NULL);
    return 0;
}