#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/stat.h>
#include "./deps/b64/b64.h"
#define HANDSHARKKEY "Sec-WebSocket-Key"
#define CRYPTOSTR "258EAFA5-E914-47DA-95CA-C5AB0DC85B11"
#define MAXFRAMESIZE 131072
typedef enum {
    CONTINUE = 0x0,
    TEXT = 0x1,
    BINARY = 0x2,
    CLOSE = 0x8,
    PING = 0x9,
    PONG = 0xA,
} OPCODE;


int make_server(char * port);
void showHttpRequestLine(FILE * fp);
void showHttpRequestHeader(FILE * fp);
int getHandSharkKey(FILE * fp, char *);
char * getEncodeText(char * key);
int handsharkresponse(int fd, char * accpet);
int heartDetect(int fd);
int sendTextMsg(int fd, char *);
void * decodeFrame(int fd);
int sendMsg(int sock, char * filepath);
void sendFrame(int fd, int fin, OPCODE code, char * data, unsigned long len);




