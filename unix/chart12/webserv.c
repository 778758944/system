#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h> 
#include <unistd.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <pthread.h>
#include <dirent.h>
#include <fcntl.h>
#include <ctype.h>
#include "./socketlib.h"
/*what is the difference between the string.h and strings.h*/

#define oops(m) {perror(m); exit(1);}

int request_times = 0;
unsigned long bodyLen;

void read_til_crnl(FILE *fp);
void process_rq(char *requesr, int fd);
void cannot(int fd);
bool not_exist(char * arg);
void do_404(char * arg, int fd);
bool isadir(char *arg);
void do_ls(char *arg, int fd);
void header(FILE *fp, char *type);
char * file_type(char * f);
bool end_in_cgi(char * argv);
void do_exe(char * argv, int fd);
void do_cat(char* arg, int fd);
void * req_call(void *);
void setup(pthread_attr_t * arrt);
void do_status(int fd);
void handle_post(int fd);
void record(FILE * fp, char * str);
static FILE * logp;
void do_json_test(int fd);
void tolowercase(char * str);

void tolowercase(char * str) {
    size_t len = strlen(str);
    for(int i = 0; i < len; i++) {
        str[i] = tolower(str[i]);
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        oops("Usage:");
    }
    int sock_id, sock_fp;
    FILE *pin, *pout;
    char request[BUFSIZ];
    pthread_attr_t pattr;
    pthread_t worker;

    sock_id = make_server_socket(argv[1]);
    
    if (sock_id == -1) {
        oops("create server");
    }

    setup(&pattr);

    while(1) {
        sock_fp = accept(sock_id, NULL, NULL);
        if (sock_fp == -1) {
            oops("accept error");
        }

        // pthread_create(&worker, &pattr, req_call, &sock_fp);
        req_call(&sock_fp);

        /*
        pin = fdopen(sock_fp, "r");

        fgets(request, BUFSIZ, pin);
        printf("get a call, request = %s\n", request);
        read_til_crnl(pin);
        process_rq(request, sock_fp);

        fclose(pin);
        */
    }
}
void setup(pthread_attr_t * attr) {
    pthread_attr_init(attr);
    pthread_attr_setdetachstate(attr, PTHREAD_CREATE_DETACHED);
}

void * req_call(void * fp) {
    if ((logp = fopen("./log", "a")) == NULL) {
        oops("create log file:");
    }
    int * sock_p = (int *) fp;
    FILE * pin;
    char request[BUFSIZ];
    pin = fdopen(*sock_p, "r");
    fgets(request, BUFSIZ, pin);
    printf("get a call, request = %s\n", request);
    record(logp, request);
    read_til_crnl(pin);
    process_rq(request, *sock_p);
    fclose(logp);
    fclose(pin);
    close(*sock_p);
    return NULL;
}



void read_til_crnl(FILE * fp) {
    char buf[BUFSIZ];
    while(fgets(buf, BUFSIZ, fp) != NULL && strcmp(buf, "\r\n") != 0) {
        printf("%s", buf);
        tolowercase(buf);
        char * col_p = strchr(buf, ':') + 2;
        if (strstr(buf, "content-length")) {
            sscanf(col_p, "%ld", &bodyLen);
            printf("bodyLen = %ld\n", bodyLen);

        }

    }

    char * buf2 = malloc(bodyLen);
    memset(buf2, 0, bodyLen);
    

    fread(buf2, bodyLen, 1, fp);

    fwrite(buf2, bodyLen, 1, stdout);
    fflush(stdout);

    puts("header done");
}

void process_rq(char *rq, int fd) {
    puts("processing");
    char method[BUFSIZ], arg[BUFSIZ];

    // drop fork
    /*
    if (fork() != 0) {
        return;
    }
    */

    strcpy(arg, ".");
    if (sscanf(rq, "%s%s", method, arg+1) != 2) {
        return;
    }

    printf("method %s\n", method);

    if (strcmp(arg+2, "status") == 0) {
        do_status(fd);
    } else if (strcmp(method, "GET") != 0) {
        puts("not get");
        if (strcmp(method, "POST") == 0) {
            puts("post request");
            handle_post(fd);
        } else {
            cannot(fd);
        }
    } else if (isadir(arg)) {
        do_ls(arg, fd);
    } else if (end_in_cgi(arg)) {
        do_exe(arg, fd);
    } else if (not_exist(arg)) {
        do_404(arg, fd);
    } else {
        do_cat(arg, fd);
        // do_json_test(fd);
    }

    request_times++;

}

void cannot(int fd) {
    FILE * fp;
    fp = fdopen(fd, "w");
    fprintf(fp, "HTTP/1.1 501 Not Implementd\r\n");
    fprintf(fp, "Content-type: text/plain\r\n");
    fprintf(fp, "\r\n");

    fprintf(fp, "That command is not yet implemented");
    fclose(fp);
}

bool not_exist(char *arg) {
    struct stat info;
    return (stat(arg, &info) == -1);
}

void do_404(char * item, int fd) {
    puts("do 404");
    FILE * fp;
    fp = fdopen(fd, "w");
    fprintf(fp, "HTTP/1.1 404 Not Found\r\n");
    fprintf(fp, "Content-type: text/plain\r\n");
    fprintf(fp, "\r\n");

    fprintf(fp, "The item %s you request is not found\n", item);
    fclose(fp);
}

bool isadir(char *arg) {
    struct stat info;
    stat(arg, &info);
    return S_ISDIR(info.st_mode);
}

void header(FILE *fp, char *type) {
    fprintf(logp,"HTTP/1.1 200 OK\r\n" );
    fprintf(fp, "HTTP/1.1 200 OK\r\n");
    if (type) {
        fprintf(fp, "Content-type: %s\r\n", type);
    }
}

void do_ls(char * dir, int fd) {
    puts("do_ls");
    FILE * fp;
    fp = fdopen(fd, "w");

    header(fp, "text/plain");
    fprintf(fp, "\r\n");
    // force buffer to ouput before close
    //fflush(fp);

    //dup2(fd, 1);
    //dup2(fd, 2);
    // close(fd);

    //execlp("/bin/ls", "ls", "-l", dir, NULL);
    //perror("dir");
    //exit(1);
    DIR * d;
    struct dirent * dir_data;
    if ((d = opendir(dir)) == NULL) {
        oops("readdir");
    }

    dir_data = readdir(d);
    while((dir_data = readdir(d)) != NULL) {
        fprintf(fp, "%s\n", dir_data->d_name);
    }

    fclose(fp);


    
}

char * file_type(char * f) {
    char * cp;
    if ((cp =strrchr(f, '.')) != NULL) {
        return cp + 1; 
    }

    return "";
}

bool end_in_cgi(char * argv) {
    printf("argv is %s\n", argv);
    char * end = file_type(argv);
    return strcmp(end, "cgi") == 0;
}

void do_exe(char * argv, int fd) {
    int pid;
    FILE * fp;
    fp = fdopen(fd, "w");
    header(fp, "text/plain");
    fprintf(fp, "\r\n");
    // fprintf(fp, "hello");
    fflush(fp);

    pid = fork();
    if (pid == 0) {
        dup2(fd, 1);
        dup2(fd, 2);
        close(fd);
        execl("./hello.cgi", "hello.cgi", NULL);
        oops("cgi error");
    } else {
        // fflush(fp);
        wait(NULL);
        puts("child over");
        // close(fd);
    }
    /*
    dup2(fd, 1);
    dup2(fd, 2);
    close(fd);
    execl(argv, argv, NULL);
    exit(1);
    */
}

void do_cat(char * arg, int fd) {
    puts("do_cat");
    FILE * fp;
    fp = fdopen(fd, "w");
    char * end =  file_type(arg+1);
    FILE * end_fp;
    char c;
    int size;
    printf("end is %s\n", end);
    if (strcmp(end, "html") == 0) {
        header(fp, "text/html");
    } else if (strcmp(end, "gif") == 0) {
        header(fp, "image/gif");
    } else if (strcmp(end, "png") == 0) {
        header(fp, "image/png");
    } else if (strcmp(end, "jpg") == 0) {
        header(fp, "image/jpg");
    } else {
        header(fp, "text/plain");
    }

    fprintf(fp, "\r\n");
    fflush(fp);
    // fclose(fp);

    // dup2(fd, 1);
    // dup2(fd, 2);
    // close(fd);
    if ((end_fp = fopen(arg, "r")) == NULL) {
        oops("file open error");
    }

    fseek(end_fp, 0, SEEK_END);
    size = ftell(end_fp);
    fseek(end_fp, 0, SEEK_SET);

    for(int i = 0; i < size; i++) {
        putc(getc(end_fp), fp);
    }


    // fflush(fp);

    fclose(end_fp);

    fclose(fp);


    // execlp("/bin/cat", "cat", arg, NULL);
    // exit(1);
}

void do_status(int fd) {
    FILE * fp;
    fp = fdopen(fd, "w");
    header(fp, "text/plain");
    fprintf(fp, "\r\n");
    fprintf(fp, "request times %d\n", request_times);
    fclose(fp);
}

void handle_post(int fd) {
    puts("to post");
    char buf[BUFSIZ];
    int nread;
    FILE * fp;
    fp = fdopen(fd, "w");
    char c;
    puts("to read post");
    /*
    if (fgets(buf, BUFSIZ, fp) != NULL) {
        puts("dede");
        printf("receive data: %s\n", buf);
        fflush(stdout);
    }
    */
   /*
    fread(buf, 0, 1, fp);
    printf("receive data: %s\n", buf);
    fflush(stdout);
    */
    puts("read done");
    header(fp, "text/plain");
    fprintf(fp, "\r\n");
    fprintf(fp, "hahahahaaaha");
    fflush(fp);
    fclose(fp);
    printf("responsed data");
    fflush(stdout);
    // puts("hahah");
}


void record(FILE * fp, char * str) {
    fputs(str, fp);
}


void do_json_test(int fd) {
    FILE * fp = fdopen(fd, "w");
    header(fp, "application/json");

    fprintf(fp, "\r\n");

    fputs("{\"name\": \"jack\"}", fp);

    fclose(fp);
}





