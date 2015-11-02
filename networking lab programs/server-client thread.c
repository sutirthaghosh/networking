#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<stdio.h>
#include<string.h>
#include<pthread.h>
int comm[100];
int count=0;
void *worker(void *arg){
char recv[100];
int x= (int)arg;
int i=0;
while(1){
bzero(recv,100);
read(x,recv,100);
//printf("%s",recv);
//fgets(recv,100,stdin);
for(i=0;i<count;i++){
if(comm[i]!=x)
write(comm[i],recv,strlen(recv)+1);
}
}
close(comm);
return NULL;}

int main(){
pthread_t pth[10];
char send[100],recv[100],ch;
int list,count_client=0;
struct sockaddr_in serv;

list=socket(AF_INET,SOCK_STREAM,0);

bzero(&serv,sizeof(serv));
serv.sin_family=AF_INET;
serv.sin_addr.s_addr=htons(INADDR_ANY);
serv.sin_port=htons(22000);


bind(list,(struct sockaddr *)&serv,sizeof(serv));

listen(list,10);

while(1){
comm[count]=accept(list,(struct sockaddr*)NULL,NULL);

pthread_create(&pth[count],NULL,worker,(void *)comm[count]);
count++;

}
pthread_join(pth[0],NULL);
return(0);
}


#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
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

fd_set readfdset;
while(1){

FD_ZERO(&readfdset);
FD_SET(0,&readfdset);
FD_SET(sock_fd,&readfdset);
select(FD_SETSIZE,&readfdset,NULL,NULL,NULL);

bzero(sendline,100);
bzero(recvline,100);

if(FD_ISSET(0,&readfdset)){
fgets(sendline,100,stdin);
write(sock_fd,sendline,strlen(sendline)+1);
}
if(FD_ISSET(sock_fd,&readfdset)){
read(sock_fd,recvline,100);
printf("%s",recvline);
}

}
return(0);}
