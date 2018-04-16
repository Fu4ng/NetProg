#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

#define PROTOPORT 8787
#define QLEN 6

int visits = 0;

int main(int argc,char * argv[]){
    struct hostent *ptrh;
    struct sockaddr_in servaddr;
    struct sockaddr_in clientaddr;
    int listenfd;
    int clientfd;
    int port;
    int alen;
    char buf[1000];

    memset( (char*)& servaddr,0,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;

    if (argc > 1){
    port = atoi(argv[1]);
    }else{
        port = PROTOPORT;
    }
    if(port > 0){
        servaddr.sin_port = htons((u_short)port);
    }else{
        fprintf(stderr,"bad port number %s\n",argv[1]);
        exit(1);
    }
    
    listenfd = socket(AF_INET,SOCK_STREAM,0);
    if(listenfd<0){
        fprintf(stderr,"socket creation failed\n");
        exit(1);
    }
    if(bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr))<0){
        fprintf(stderr,"bind failed\n");
        exit(1);
    }
    if(listen(listenfd,QLEN)<0){
        fprintf(stderr,"accept failed\n");
        exit(1);
    }
    while(1){
        alen = sizeof(clientaddr);
        if((clientfd = accept(listenfd,(struct sockaddr *)& clientaddr,&alen))<0){
            fprintf(stderr,"accept failed\n");
            exit(1);
        }
    visits++;
    sprintf(buf,"this server has been contacted %d time \n",visits);
    send(clientfd,buf,strlen(buf),0);
    close(clientfd);
    }
}








