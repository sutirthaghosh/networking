#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netdb.h>
#include<unistd.h>
#include<sys/un.h>
#include<netinet/in.h>
int main(){
int sock;
char buffer[100];
char recv_from_addr[100];
ssize_t size;
sock=socket(PF_INET,SOCK_DGRAM,0);
struct sockaddr_in address;

address.sin_family=AF_INET;
address.sin_port=htons(59670);
address.sin_addr.s_addr=htonl(INADDR_ANY);
//inet_pton(AF_INET,"1.2.3.110",&(address.sin_addr));

struct sockaddr_in receivedfrom;
socklen_t length;

if(bind(sock,(struct sockaddr *)&address,sizeof(address))<0){
printf("error binding");
exit(EXIT_FAILURE);
}
while(1){

//size=recvfrom(sock,buffer,(size_t)(sizeof(buffer)),0,(struct sockaddr *) &receivedfrom,&length);
read(sock,buffer,sizeof(buffer));
printf("%s",buffer);
memset(buffer,'\0',(size_t)sizeof(buffer));
}

inet_ntop(AF_INET,(void *)&receivedfrom.sin_addr,recv_from_addr,(socklen_t)(sizeof(recv_from_addr)));
printf("%s \n",recv_from_addr);

}
