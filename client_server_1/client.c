#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>
#include<string.h>
void main(){
int sock;
char buffer[100];
struct sockaddr_in addr;
addr.sin_family=AF_INET;
addr.sin_port=htons(52369);
inet_pton(AF_INET,"127.0.0.1",&(addr.sin_addr));

sock=socket(PF_INET,SOCK_STREAM,0);
connect(sock,(struct sockaddr*)&addr,sizeof(addr));

fd_set readfdset;
	while(1){
	FD_ZERO(&readfdset);
	FD_SET(0,&readfdset);
	FD_SET(sock,&readfdset);
	select(FD_SETSIZE,&readfdset,NULL,NULL,NULL);
		if(FD_ISSET(sock,&readfdset)){
			memset(buffer,'\0',sizeof(buffer));
			read(sock,buffer,sizeof(buffer));
			printf("%s",buffer);	
		}

		if(FD_ISSET(0,&readfdset)){
			memset(buffer,'\0',sizeof(buffer));
			read(0,buffer,sizeof(buffer));
			write(sock,buffer,sizeof(buffer));
		}

	}        
}
