#include <stdio.h>
#include <signal.h>
#include <unistd.h>
void handle (int, struct __siginfo *, void *);
static int num = 0;
int main() {
   struct sigaction newsigaction;
   char input[100];
   sigset_t blocked;
   printf("pid is %d\n", getpid());
   /*
    SA_SIGINFO：get more information of the signal
    SA_RESETHAND: delete the handle after called it
    SA_RESTART: restart the slow system call
    SA_NODEFER: can be recursed;
   */
   newsigaction.sa_flags = SA_SIGINFO | SA_RESTART;
   newsigaction.__sigaction_u.__sa_sigaction = handle;
   sigemptyset(&blocked);
   sigaddset(&blocked, SIGQUIT);
   newsigaction.sa_mask = blocked;
   sigaction(SIGINT, &newsigaction, NULL);
//    sigaction(SIGQUIT, &newsigaction, NULL);
   while (1) {
       gets(input);
       puts(input);
   }
   return 0;
}
/*
param
s SIGINT
*/
void handle (int s, struct __siginfo * siginfo, void * p) {
    puts("start...");
    num += 1;

    if (s == SIGINT) {
        puts("SIGINT\n");
    } else {
        puts("SIGQUIT\n");
    }
    
    /*
    printf("handling\n");
    printf("pid is %d\n", siginfo->si_pid);
    if (s == SIGINT) {
        puts("true");
    } else {
        puts("false");
    }
    */
    sleep(5);
    printf("%d\n", num);
    puts("leaving");
}

