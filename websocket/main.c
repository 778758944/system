#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include "./websocket.h"
#define FORHEART "hello"
#define oops(m) {perror(m); exit(1);}

void setup(pthread_attr_t * attr);


void setup(pthread_attr_t * attr) {
    pthread_attr_init(attr);
    pthread_attr_setdetachstate(attr, PTHREAD_CREATE_DETACHED);
}

void * handleNewSocket(void *);

void * handleNewSocket(void * p) {
    int fd;
    char key[BUFSIZ];
    char * acceptKey;
    FILE * fp;
    fd = *((int *) p);
    fp = fdopen(fd, "r");
    showHttpRequestLine(fp);
    getHandSharkKey(fp, key);
    acceptKey = getEncodeText(key);
    handsharkresponse(fd, acceptKey);
    decodeFrame(fd);
    /*
    while (decodeFrame(fd)) {
        sendFrame(fd, 1, 0x9, FORHEART, strlen(FORHEART));
    } 
    */
    // decodeFrame(fd);
    // sendMsg(fd, "./m.mp3");
    printf("send message to client");
    sendTextMsg(fd, "hello, websocket");
    close(fd);
    return NULL;
}

int main(int argc, char **argv) {
    int fd;
    char key[BUFSIZ];
    char * accpet;
    int sock_id = make_server(argv[1]);
    FILE * fp;

    if (sock_id == -1) {
        oops("server error:");
    }



    while (1) {
        int pid;
        pthread_t t;
        pthread_attr_t attr;
        struct sockaddr_in connaddr;
        uint32_t connaddr_len;
        char ip[100];
        fd = accept(sock_id, NULL, NULL);
        printf("receive req\n");
        getsockname(fd, &connaddr, &connaddr_len);
        inet_ntop(AF_INET, (struct sockaddr *) &connaddr.sin_addr.s_addr, ip, 100);
        printf("ip: %s, port: %d\n", ip, ntohs(connaddr.sin_port));
        

        setup(&attr);
        pthread_create(&t, &attr, handleNewSocket, &fd);
        
        /*
        fp = fdopen(fd, "r");
        showHttpRequestLine(fp);
        getHandSharkKey(fp, key);
        accpetKey = getEncodeText(key);
        handsharkresponse(fd, accpetKey);
        sleep(2);
        decodeFrame(fd);
        // sendTextMsg(fd, "hello, websocket");
        // sendFile("./girl.jpg", fd);
        // heartDetect(fd);
        // sleep(5);
        // sendTextMsg(fd, "hello, websocket");
        sendMsg(fd, "./m.mp3");
        */
    }
}