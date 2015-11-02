#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netdb.h>
#include<unistd.h>
#include<sys/un.h>
#include<netinet/in.h>
int main(){
int sock;
char buffer[100]="test";
char recv_from_addr[100];
ssize_t size;
sock=socket(PF_INET,SOCK_DGRAM,0);
struct sockaddr_in address;
struct sockaddr_in send_address;
//setting source port ,address etc
address.sin_family=AF_INET;
address.sin_port=htons(55000);
address.sin_addr.s_addr=htonl(INADDR_ANY);
if(bind(sock,(struct sockaddr *)&address,sizeof(address))<0){
printf("error binding");
exit(EXIT_FAILURE);
}
// destination port ,address etc
send_address.sin_family=AF_INET;
send_address.sin_port=htons(55000);
inet_pton(AF_INET,"182.79.224.25",&(send_address.sin_addr));

struct sockaddr_in receivedfrom;
socklen_t length;


while(1){

size=sendto(sock,buffer,(size_t)(sizeof(buffer)),0,(struct sockaddr *) &send_address,(socklen_t)(sizeof(send_address)));
sleep(1);
//write(sock,"test",4);
//printf("%s",buffer);
//memset(buffer,'\0',(size_t)sizeof(buffer));
}

}
