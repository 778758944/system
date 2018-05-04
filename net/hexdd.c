#include <arpa/inet.h>
#include <stdio.h>
#define HOSTSIZE 30
int main() {
    int h1 = ntohl(0xd950c40), h2 = ntohl(0x0fffffff), h3 = ntohl(0x7f000001);
    char *d1 = "205.188.160.121",
         *d2 = "64.12.149.13",
         *d3 = "205.188.146.23";
    int hdest1, hdest2, hdest3;
    char ddest1[HOSTSIZE],
         ddest2[HOSTSIZE],
         ddest3[HOSTSIZE]; 
    inet_pton(AF_INET, d1, &hdest1);
    inet_pton(AF_INET, d2, &hdest2);
    inet_pton(AF_INET, d3, &hdest3);

    inet_ntop(AF_INET, &h1, ddest1, HOSTSIZE);
    inet_ntop(AF_INET, &h2, ddest2, HOSTSIZE);
    inet_ntop(AF_INET, &h3, ddest3, HOSTSIZE);

    printf("%s = %x\n", d1, htonl(hdest1));
    printf("%s = %x\n", d2, htonl(hdest2));
    printf("%s = %x\n", d3, htonl(hdest3));

    printf("%x = %s\n", h1, ddest1);
    printf("%x = %s\n", h2, ddest2);
    printf("%x = %s\n", h3, ddest3);
    return 0;
}