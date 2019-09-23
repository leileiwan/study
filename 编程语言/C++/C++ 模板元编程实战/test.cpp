#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pthread.h"
#include "unistd.h"
#include "sys/types.h"

static int search(char*s,char*t)
{	
int size_t=strlen(t),size_s=strlen(s),T,i,j;
char *p=NULL;
for(i=0;i<=(size_s-size_t);i++)
{
p=s+i;
T=1;
for(j=0;j<size_t;j++)
{
if(*p!=*(t+j))
{
T=0;
break;
}
p++;
}
if(T==1)
break;
}
if(T==0)
return 0;
else
return 1;
}

void *test_fun(void* arg){
    system("/home/dev/qq8/detect_txupd.py");
    return NULL;
}
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void printids(const char *s){
    pid_t pid;
    pthread_t tid;
    pid = getpid();
    tid = pthread_self();
    printf("%s, pid %lu tid %lu (0x%lx)\n",s,(unsigned long)pid,(unsigned long)tid,
    (unsigned long)tid);
}

void *thread_func(void *arg){
    printids("new thread: ");
    return ((void*)0);
}
int main() {
    int err;
    pthread_t tid;
    err = pthread_create(&tid,NULL,thread_func,NULL);
    if (err != 0) {
        fprintf(stderr,"create thread fail.\n");
    exit(-1); 
    }
    printids("main thread:");
    sleep(1);   
    return 0;
}


// TRACE("%p CtlID=%u lpnmh->code=%x\n",This,CtlID,lpnmh->code);
