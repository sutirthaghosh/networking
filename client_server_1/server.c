//server used to chat with client 
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>
#include<string.h>
void main(){
int client,server;
char buffer[100];
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

fd_set readfdset;
	while(1){
	FD_ZERO(&readfdset);
	FD_SET(0,&readfdset);
	FD_SET(client,&readfdset);
	select(FD_SETSIZE,&readfdset,NULL,NULL,NULL);
		if(FD_ISSET(client,&readfdset)){
			memset(buffer,'\0',sizeof(buffer));
			read(client,buffer,sizeof(buffer));
			printf("%s",buffer);	
		}

		if(FD_ISSET(0,&readfdset)){
			memset(buffer,'\0',sizeof(buffer));
			read(0,buffer,sizeof(buffer));
			write(client,buffer,sizeof(buffer));
		}

	}        

}
