/*
protocol:
client: HELLO mypid
server: TICK ticketid FAIL no ticket
client: GBYE ticketid
server: THNX message
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
int setup(char * hostname, char * portnum);
int get_ticket();
int release_ticket();