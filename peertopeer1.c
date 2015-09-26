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
char address[100],buffer[5000],user_name[100],b[5000],terminate[]="bye\n";
uint32_t addr;
int sock_server,sock_client_init,sock_client,already_connected=0,e;
struct sockaddr_in servername;
struct sockaddr_in client;
struct sockaddr_in x;
socklen_t y=sizeof(x);
char ca[100];
socklen_t lenght;
lenght=sizeof(client);
printf("please press \"x\" to exit...");
printf("\n enter your name(no space allowed) to start chat : ");
scanf("%s",user_name);
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
sock_client=accept(sock_server,(struct sockaddr *)&client,&lenght);
if(sock_client!=-1)
already_connected=1;
addr=client.sin_addr.s_addr;
getsockname(sock_client,(struct sockaddr*)&x,&y);
inet_ntop(AF_INET,&(x.sin_addr),ca,&y);
printf("%s\n has established a connection to you...",ca);
FD_SET(sock_client,&readfdset);
FD_SET(sock_client,&writefdset);
}
//if connected and data available then read

if(already_connected==1 && FD_ISSET(sock_client,&readfdset)){
read(sock_client,buffer,sizeof(buffer));
if(strcmp(buffer,terminate)==0){
    printf("seems ur friend has gone off line.........");
            break;
        }
printf(ANSI_COLOR_RED"%s"ANSI_COLOR_RESET"\n",buffer);
}

if((already_connected==2) && FD_ISSET(sock_client_init,&readfdset) ){
read(sock_client_init,buffer,sizeof(buffer));
if(strcmp(buffer,terminate)==0){
    printf("seems ur friend has gone off line.........");
    break;
        }
printf(ANSI_COLOR_YELLOW"%s"ANSI_COLOR_RESET"\n",buffer);
}

if(FD_ISSET(0,&readfdset)){
    memset(b,'\0',sizeof(b));
    memset(buffer,'\0',sizeof(buffer));
    read(0,b,sizeof(b));
    strcat(buffer,user_name);
    strcat(buffer," : ");
    strcat(buffer,b);
    if(strcmp(b,terminate)==0){
    printf("OK terminating all connections.........");
    memset(buffer,'\0',sizeof(buffer));
    strcpy(buffer,terminate);
        }
    if (already_connected==0){
            connect(sock_client_init,(struct sockaddr *)&servername,(socklen_t)sizeof(servername));
            FD_SET(sock_client_init,&readfdset);
            FD_SET(sock_client_init,&writefdset);
            already_connected=2;
        }
    if(already_connected==1){
            write(sock_client,buffer,strlen(buffer)+1);
        }
    if(already_connected==2 ){
       write(sock_client_init,buffer,strlen(buffer)+1);
       }
       if(strcmp(b,terminate)==0)
        break;
    }
}


shutdown(sock_server,2);
if(already_connected==1)
shutdown(sock_client,2);
if(already_connected==2)
shutdown(sock_client_init,2);
printf("done ,see u soon....\n designed by ..Sutirtha Ghosh.........\n");
return 0;}
