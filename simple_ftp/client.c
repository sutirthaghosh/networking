#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>
#include<string.h>
void main(){
int sock;
size_t size;
FILE *fp;
fp=fopen("downloaded","wb");
char buffer[1024];
struct sockaddr_in addr;
addr.sin_family=AF_INET;
addr.sin_port=htons(52369);
inet_pton(AF_INET,"127.0.0.1",&(addr.sin_addr));

sock=socket(PF_INET,SOCK_STREAM,0);
connect(sock,(struct sockaddr*)&addr,sizeof(addr));

	while(1){
	size=read(sock,buffer,1024);
	fwrite(buffer,sizeof(char),size,fp);
	printf("received %d bytes \n",(int)size);
	if(size<1024)
	break;
	}        
}
