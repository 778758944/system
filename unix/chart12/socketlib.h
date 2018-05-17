#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <strings.h>
#define HOSTNAME "0.0.0.0"

int make_server_socket(char *portnum);
int connect_to_server(char *hostname, char *portnum);