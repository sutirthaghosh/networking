#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<string.h>
void main()
{
struct hostent *x;
char name[100],address[200];
scanf("%s",name);
x=gethostbyname(name);
inet_ntop(AF_INET,x->h_addr,address,sizeof(address));
printf("%s\n",address);
}
