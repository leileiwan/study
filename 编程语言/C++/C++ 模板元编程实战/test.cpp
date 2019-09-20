#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pthread.h"

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
    system("sleep 5");
    printf("zz");
    return NULL;
}
int main(){
    
    pthread_t ntid;
    int err=pthread_create(&ntid,NULL,test_fun,NULL);
    if(err!=0){
        printf("create thread error...");
    }
    // pthread_join(ntid,NULL);
    printf("hello world!");
    
    while(1){
        system("sleep 1");
    }
    return 0;
}

// TRACE("%p CtlID=%u lpnmh->code=%x\n",This,CtlID,lpnmh->code);
