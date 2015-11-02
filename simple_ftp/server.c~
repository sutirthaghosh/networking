//server used to chat with client 
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>
#include<string.h>
void main(){
FILE *fp;
fp=fopen("testfile","rb");
size_t bsize;
int client,server;
char buffer[1024];
struct sockaddr_in serveraddr;
serveraddr.sin_family=AF_INET;
serveraddr.sin_port=htons(52369);
serveraddr.sin_addr.s_addr=htonl(INADDR_ANY);
//creating the socket
server=socket(PF_INET,SOCK_STREAM,0);
//binding socket with proper config
bind(server,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
//listen to the port
listen(server,1);
// accept connection
client=accept(server,NULL,NULL);

bsize=fread(buffer,sizeof(char),1024,fp);
	while(bsize>0){
	write(client,buffer,bsize);
	printf("sending %d bytes \n",(int)bsize);
	bsize=fread(buffer,sizeof(char),1024,fp);	
	}        
printf("transfer complete");
}
