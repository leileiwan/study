#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main(){
    char *s = "./drive_c/users/dev/Application Data/Tencent/QQ/AuTemp/2653170047/NewUpd/txupd.exe";
    char *p="tdxupd.exe";
    int res=search(s,p);
    printf("%d\n",res);
    system("python ");
    return 0;
}

TRACE("%p CtlID=%u lpnmh->code=%x\n",This,CtlID,lpnmh->code);