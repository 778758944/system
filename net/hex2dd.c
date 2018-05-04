#include <stdio.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdlib.h>
#define HOSTSIZE 30
int main(int argc, char ** argv) {
    int a;
    char ip[HOSTSIZE];
    if (argc < 2) {
        perror("Usage: hex2dd xxxx");
        exit(1);
    }

    sscanf(argv[1], "%x", &a);

    printf("a = %x\n", a);


    if (inet_ntop(AF_INET, &a, ip, HOSTSIZE) == NULL) {
        perror("error occured:");
        exit(1);
    }

    printf("%x = %s\n", a, ip);
    return 0;
    
}