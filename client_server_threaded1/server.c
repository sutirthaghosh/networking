//server used to chat with client 
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>
#include<string.h>
#include<pthread.h>
int client[100];
int noc=0;
void* my_thread(void *x){
int k=(int)(intptr_t)x,i;
char buffer[100];
fd_set readfdset;
	while(1){
	
			memset(buffer,'\0',sizeof(buffer));
			read(k,buffer,sizeof(buffer));
			for(i=0;i<noc;i++){
				if(client[i]!=k){
					write(client[i],buffer,sizeof(buffer));
				}
			}
	}        

}
void main(){
int server;
pthread_t thread[100];
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
while(1){
client[noc]=accept(server,NULL,NULL);
pthread_create(&thread[noc],NULL,my_thread,(void *)(intptr_t)(client[noc]));
noc++;
}
}
