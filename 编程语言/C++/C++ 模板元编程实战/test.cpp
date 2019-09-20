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
int main(){
    //创建子进程
    pid_t pid = fork();
    if(pid==-1){
        FIXME("创建子进程失败");
        return 1;
    }
    //判断是否是子进程  
    if(pid==0){
        // int ret=execl("/usr/bin/python","pyton","/home/wanlei/Desktop/test.py",NULL);
        puts("I'm child");
        execl("/usr/bin/python","pyton","/home/wanlei/Desktop/test.py",NULL);

        puts("sleep 5s ...");
        sleep(5);
        puts("sleep end");

        printf("子进程PID是%d\n", getpid());
        printf("父进程PID是%d\n", getppid());

        return 0;
    }
    else{
        puts("I'm parent");

        printf("子进程PID是%d\n", pid);
        printf("父进程PID是%d\n", getpid());
        system("sleep 20");
    }
    
    
    
    
    printf("hello\n");
    return 0;
}

// TRACE("%p CtlID=%u lpnmh->code=%x\n",This,CtlID,lpnmh->code);
