#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<stdio.h>
#include<string.h>
int main(){
char send[100],recv[100],ch;
int list,comm;
struct sockaddr_in serv;

list=socket(AF_INET,SOCK_STREAM,0);

bzero(&serv,sizeof(serv));
serv.sin_family=AF_INET;
serv.sin_addr.s_addr=htons(INADDR_ANY);
serv.sin_port=htons(22000);


bind(list,(struct sockaddr *)&serv,sizeof(serv));

listen(list,10);

comm=accept(list,(struct sockaddr*)NULL,NULL);
printf("press x to exit");
do{
bzero(recv,100);
bzero(send,100);
read(comm,recv,100);
if(strcmp(recv,"L")==0)
printf("client has left");
else{
printf("received-%s",recv);
fgets(recv,100,stdin);
write(comm,recv,strlen(recv)+1);
if(strcmp())
}
//fgets(send,100,stdin);
printf("echoing back - %s",recv);
write(comm,recv,strlen(recv)+1);

}while(recv[0]!='L'||send[0]!='L');  
printf("EXITING..............");          
return(0);}













#include<sys/types.h>
#include<sys/types.h>
#include<netdb.h>
#include<stdio.h>
#include<string.h>
int main(){
int sock_fd,n;
char sendline[100];
char recvline[100];
struct sockaddr_in servaddr;

sock_fd=socket(AF_INET,SOCK_STREAM,0);

bzero(&servaddr,sizeof(servaddr));

servaddr.sin_family=AF_INET;
servaddr.sin_port=htons(22000);
inet_pton(AF_INET,"127.0.0.1",&(servaddr.sin_addr));

connect(sock_fd,(struct sockaddr*)&servaddr,sizeof(servaddr));

while(1){
bzero(sendline,100);
bzero(recvline,100);
fgets(sendline,100,stdin);
write(sock_fd,sendline,strlen(sendline)+1);
read(sock_fd,recvline,100);
printf("%s",recvline);
}
return(0);}
