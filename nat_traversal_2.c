#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netdb.h>
#include<unistd.h>
#include<sys/un.h>
#include<sys/types.h>
#include<netinet/in.h>
int main(){
int sock;
char buffer[100]="test";
char readbuffer[100];
char recv_from_addr[100];
int t=0;
// read timeout structure
struct timeval timeout;
timeout.tv_sec=1;
timeout.tv_usec=0;
ssize_t size;
sock=socket(PF_INET,SOCK_DGRAM,0);
struct sockaddr_in address;
struct sockaddr_in send_address;
struct sockaddr_in send1_address;
//setting source port ,address etc
address.sin_family=AF_INET;
address.sin_port=htons(44000);
address.sin_addr.s_addr=htonl(INADDR_ANY);
if(bind(sock,(struct sockaddr *)&address,sizeof(address))<0){
printf("error binding");
exit(EXIT_FAILURE);
}
// destination port ,address etc
send_address.sin_family=AF_INET;
send_address.sin_port=htons(44000);
inet_pton(AF_INET,"125.22.78.54",&(send_address.sin_addr));

send1_address.sin_family=AF_INET;
send1_address.sin_port=htons(44000);
inet_pton(AF_INET,"182.66.115.155",&(send1_address.sin_addr));

struct sockaddr_in receivedfrom;
socklen_t length;

fd_set readfdset;
while(1){
memset(readbuffer,'\0',(size_t)sizeof(readbuffer));
FD_ZERO(&readfdset);
FD_SET(sock,&readfdset);
FD_SET(0,&readfdset);

t=select(FD_SETSIZE,&readfdset,NULL,NULL,&timeout);
if(FD_ISSET(sock,&readfdset)){
    read(sock,readbuffer,sizeof(readbuffer));
    printf("%s",readbuffer);
    memset(readbuffer,'\0',(size_t)sizeof(readbuffer));
}
if(FD_ISSET(0,&readfdset)){
    read(0,readbuffer,sizeof(readbuffer));
    printf("%s",readbuffer);
    size=sendto(sock,readbuffer,(size_t)(sizeof(readbuffer)),0,(struct sockaddr *) &send_address,(socklen_t)(sizeof(send_address)));
    size=sendto(sock,readbuffer,(size_t)(sizeof(readbuffer)),0,(struct sockaddr *) &send1_address,(socklen_t)(sizeof(send1_address)));
    memset(readbuffer,'\0',(size_t)sizeof(readbuffer));
}
size=sendto(sock,buffer,(size_t)(sizeof(buffer)),0,(struct sockaddr *) &send_address,(socklen_t)(sizeof(send_address)));
size=sendto(sock,buffer,(size_t)(sizeof(buffer)),0,(struct sockaddr *) &send1_address,(socklen_t)(sizeof(send1_address)));
if(t==0)
sleep(1);
}

}
