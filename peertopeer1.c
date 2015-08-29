#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<string.h>
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void init_sockaddr(struct sockaddr_in *name,char * address,uint16_t port){
name->sin_family=AF_INET;
name->sin_port=htons(port);
inet_pton(AF_INET,address,&(name->sin_addr));
}
//initialize and bind the server socket
int create_socket(uint16_t port){
int sock;
struct sockaddr_in config;
sock=socket(PF_INET,SOCK_STREAM,0);
config.sin_family=AF_INET;
config.sin_port=htons(port);
config.sin_addr.s_addr=htonl(INADDR_ANY);
bind(sock,(struct sockaddr*)&config,sizeof(config));
return(sock);
}

int main(){
char address[100],buffer[500];
int sock_server,sock_client_init,sock_client,already_connected=0;
struct sockaddr_in servername;
struct sockaddr_in client;

sock_server=create_socket(2345);

sock_client_init=socket(PF_INET,SOCK_STREAM,0);
listen(sock_server,1);
init_sockaddr(&servername,"127.0.0.1",2345);

fd_set readfdset,writefdset;
FD_ZERO(&readfdset);
FD_ZERO(&writefdset);
FD_SET(0,&readfdset);
FD_SET(sock_server,&readfdset);

while(1){
FD_ZERO(&readfdset);
FD_SET(0,&readfdset);
FD_SET(sock_server,&readfdset);
if(already_connected==1){
FD_SET(sock_client,&readfdset);
FD_SET(sock_client,&writefdset);
}
if(already_connected==2){
FD_SET(sock_client_init,&readfdset);
FD_SET(sock_client_init,&writefdset);
}
select(FD_SETSIZE,&readfdset,NULL,NULL,NULL);
//server to accept connection
if(FD_ISSET(sock_server,&readfdset)){
sock_client=accept(sock_server,(struct sockaddr *)NULL ,NULL);
if(sock_client!=-1)
already_connected=1;
FD_SET(sock_client,&readfdset);
FD_SET(sock_client,&writefdset);
}
//if connected and data available then read

if(already_connected==1 && FD_ISSET(sock_client,&readfdset)){
//memset(buffer,'\0',sizeof(buffer));
read(sock_client,buffer,sizeof(buffer));
printf(ANSI_COLOR_RED "\nRECEIVED: %s "ANSI_COLOR_RESET "\n",buffer);
}

if((already_connected==2) && FD_ISSET(sock_client_init,&readfdset) ){
//printf("sock_client_init");
memset(buffer,'\0',sizeof(buffer));
read(sock_client_init,buffer,sizeof(buffer));
printf(ANSI_COLOR_RED "\nRECEIVED: %s " ANSI_COLOR_RESET "\n",buffer);
}

// if input available in stdin then use already_connected connection or try connect to server
if(FD_ISSET(0,&readfdset)){
memset(buffer,'\0',sizeof(buffer));
//printf("stdin entry\n");
read(0,buffer,sizeof(buffer));
    if (already_connected==0){
       // printf("attempt to connect to server\n");
        connect(sock_client_init,(struct sockaddr *)&servername,(socklen_t)sizeof(servername));
        FD_SET(sock_client_init,&readfdset);
        FD_SET(sock_client_init,&writefdset);
        already_connected=2;
    }
    if(already_connected==1 &&FD_ISSET(sock_client,&writefdset)){
        write(sock_client,buffer,strlen(buffer)+1);
        }
    if(already_connected==2 && FD_ISSET(sock_client_init,&writefdset)){
       // printf("write socket_client_init \n");
       write(sock_client_init,buffer,strlen(buffer)+1);
       }
    }
}


close(sock_server);
if(already_connected==1)
close(sock_client);
if(already_connected==2)
close(sock_client_init);
return 0;}
