#include "./websocket.h"

int make_server(char * port) {
    struct addrinfo *result, dint;
    int sock_id, rc;

    memset(&dint, 0, sizeof(dint));
    
    dint.ai_family = AF_INET;
    dint.ai_socktype = SOCK_STREAM;

    rc = getaddrinfo(NULL, port, &dint, &result);

    if (rc != 0) {
        return -1;
    }

    sock_id = socket(dint.ai_family, dint.ai_socktype, dint.ai_protocol);

    if (bind(sock_id, result->ai_addr, result->ai_addrlen) != 0) {
        return -1;
    }

    freeaddrinfo(result);

    if (listen(sock_id, 10) != 0) {
        return -1;
    }

    return sock_id;
}

void showHttpRequestLine(FILE * fp) {
    char buf[BUFSIZ];
    fseek(fp, 0, SEEK_SET);
    fgets(buf, BUFSIZ, fp);
    printf("request line is %s\n", buf);
    fflush(stdout);
}

void showHttpRequestHeader(FILE * fp) {
    char buf[BUFSIZ];
    while (fgets(buf, BUFSIZ, fp) != NULL && strcmp(buf, "\r\n") != 0) {
        puts(buf);
    }
}

int getHandSharkKey(FILE * fp, char * str) {
    char header[BUFSIZ];
    fseek(fp, 0, SEEK_SET);
    while (fgets(header, BUFSIZ, fp) != NULL && strcmp(header, "\r\n") != 0) {
        printf("header is %s\n", header);
        fflush(stdout);
        char * index;
        if ((index = strchr(header, ':')) != NULL) {
            if (strncmp(HANDSHARKKEY, header, index-header) == 0) {
                strcpy(str, index + 2);
                str[strlen(str) - 2] = '\0';
                return 0;
            } 
        }
    }
    puts("loop done");
    return -1;
}

char * getEncodeText(char * key) {
    char str[BUFSIZ];
    memset(str, 0, BUFSIZ);
    unsigned char hash[SHA_DIGEST_LENGTH];
    strcat(str, key);
    strcat(str, CRYPTOSTR);
    printf("str is %s\n", str);
    SHA1((unsigned char *) str, strlen(str), hash);
    char * val = b64_encode(hash, SHA_DIGEST_LENGTH);
    printf("val %s\n", val);
    return val;
}

int handsharkresponse(int fd, char * value) {
    char res[BUFSIZ];
    char msg[BUFSIZ];
    memset(msg, 0, BUFSIZ);
    sprintf(res, "HTTP/1.1 101 Switching Protocols\r\nContent-Length: 0\r\nUpgrade: websocket\r\nConnection: Upgrade\r\nSec-WebSocket-Accept: %s\r\n\r\n", value);
    write(fd, res, strlen(res));
    return 1;
}

int heartDetect(int fd) {
    char frame[BUFSIZ];
    frame[0] = 0x89;
    frame[1] = strlen("dedede");
    strcat(frame, "dedede");
    write(fd, frame, strlen(frame));
    puts("ping send");
    decodeFrame(fd);
    return 1;
}

int sendTextMsg(int fd, char * str) {
    char msg[BUFSIZ];
    memset(msg, 0, BUFSIZ);
    msg[0] = 0x81;
    msg[1] = strlen(str);

    strcat(msg, str);
    write(fd, msg, strlen(msg));
    return 1;
}

void * decodeFrame(int fd) {
    int fin,
        opcode,
        ismask,
        readc;
    uint64_t len = 0;

    char header[2];
    char mask[4];
    char * p;

    if ((readc = read(fd, header, 2)) == 2) {
        fin = (header[0] >> 7) & 0x01;
        opcode = header[0] & 0x0F;
        ismask = (header[1] >> 7) & 0x01;
        len = header[1] & 0x7F;
        printf("fin = %d, opcode = %d, ismask = %d, len = %llu\n", fin, opcode, ismask, len);
    }

    if (len == 126) {
        char unit[2];
        if ((readc = read(fd, unit, 2)) != 2) {
            return NULL;
        }

        // why why why !!!!!
        len = ntohs(*(uint16_t *)unit);
        printf("len is %llu\n", len);
    } else if (len == 127) {
        char unit[8];
        if ((readc = read(fd, unit, 8)) != 8) {
            return NULL;
        }

        len = ntohll(*(uint64_t *)unit);
        printf("len is %llu\n", len);
    }

    if (ismask == 1) {
        if ((readc = read(fd, mask, 4)) != 4) {
            return NULL;
        }
    }


    p = (char *) malloc(len);

    if ((readc = read(fd, p, len)) != len) {
        return NULL;
    }

    if (ismask) {
        for (int i = 0; i < len; i++) {
            p[i] = p[i] ^ mask[i % 4];
        }
    }

    // need to be fixed
    if (opcode == 2 || opcode == 0) {
        puts("write to file");
        int savefd = open("./file", O_CREAT | O_APPEND | O_RDWR, 0777);
        write(savefd, p, len);
    } else {
        printf("p = %s\n", p);
    }

    free(p);

    if (fin == 0) {
        decodeFrame(fd);
    } 
    return p;
}

int sendMsg(int sock, char * filepath) {
    
    struct stat fileinfo;
    unsigned long long size;
    char * data;
    int fd;
    unsigned long readc;

    printf("%s\n", filepath);
    fflush(stdout);

    if (stat(filepath, &fileinfo) == -1) {
        return -1;
    }

    if ((fd = open(filepath, O_RDONLY)) == -1) {
        return -1;
    }
    

    size = fileinfo.st_size;

    if (size < MAXFRAMESIZE) {
        data = (char *) malloc(size);
        if ((readc = read(fd, data, size)) != size) {
            return -1;
        }
        sendFrame(sock, 1, 2, data, size);
        free(data);
    } else {
        unsigned int last = size % MAXFRAMESIZE;
        unsigned int pieces = (unsigned int) (size / MAXFRAMESIZE);
        printf("last is %u, pieces is %u\n", last, pieces);
        fflush(stdout);
        int i;
        int fin;
        for (i = 0; i < pieces; i++) {
            data = (char *) malloc(MAXFRAMESIZE);
            lseek(fd, i * MAXFRAMESIZE, SEEK_SET);
            if ((readc = read(fd, data, MAXFRAMESIZE)) != MAXFRAMESIZE) {
                return -1;
            }

            OPCODE opcode = (i == 0 ? BINARY : CONTINUE); 
            
            sendFrame(sock, 0, opcode, data, MAXFRAMESIZE);
            free(data);
        }
        
        data = (char *) malloc(last);
        lseek(fd, i * MAXFRAMESIZE, SEEK_SET);

        if ((readc = read(fd, data, last)) != last) {
            return -1;
        }

        sendFrame(sock, 1, 0, data, last);
        free(data);
    }
    close(fd);
    return 0;
}

void sendFrame(int fd, int fin, OPCODE opcode, char * data, unsigned long len) {
    printf("fin is %d, opcode %d, len is %ld\n", fin, opcode, len);
    fflush(stdout);
    unsigned long readc;
    unsigned int addsize;
    char * frame;
    int  testfd;

    // testfd = open("./ff", O_CREAT | O_TRUNC | O_RDWR, 0777);

    if (len < 126) {
        addsize = 2;
        frame = (char *) malloc(len + addsize);
        frame[0] = (fin << 7) | opcode;
        frame[1] = len;
    } else if (len < (MAXFRAMESIZE / 2)) {
        u_int16_t payloadlen;
        addsize = 4;
        frame = (char *) malloc(len + addsize);
        frame[0] = (fin << 7) | opcode;
        frame[1] = 126;
        payloadlen = htons((u_int16_t) len);
        char * p = (char *) &payloadlen;
        for (int i = 0; i < 2; i++) {
            frame[2 + i] = * (p + i);
        }
    } else {
        u_int64_t payloadlen;
        addsize = 10;
        frame = (char *) malloc(len + addsize);
        frame[0] = (fin << 7) | opcode;
        frame[1] = 127;
        payloadlen = htonll((u_int64_t) len);
        char * p = (char *) &payloadlen;
        for (int i = 0; i < 8; i++) {
            frame[2 + i] = *(p + i);
        }
    }

    int i;
    for (i = 0; i < len; i++) {
        frame[addsize+i] = data[i];
    }
    write(fd, frame, len + addsize);
    free(frame);
}

