#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>


int main(int argc, char **argv) {
    chmod(argv[1], S_IRWXU | S_IRWXG | S_IRWXO);
    return 0;
}