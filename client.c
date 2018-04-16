#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#define PROTOPORT 8787

extern int errno;

char localhost[] = "localhost";

int main(int argc,char *argv[])
{
	struct hostent *ptrh;
	struct sockaddr_in servaddr;
    int sockfd;
    int port;
    char* host;
    int n;
    char buf [1000];

    memset((char*)& servaddr,0,sizeof(servaddr));
    servaddr.sin_family=AF_INET;

    if(argc>2){
          port = atoi(argv[2]);
    }else{
        port = PROTOPORT;
    }
    if(port>0){
        servaddr.sin_port = htons((u_short)port);
    }else{
        fprintf(stderr,"bad port number %s\n",argv[2]);
        exit(1);
    }
    if(argc>1){
        host = argv[1];
    }else{
        host = localhost ;    
    }
    ptrh = gethostbyname(host);
    if((char*)ptrh == NULL){
        fprintf(stderr,"invaild host:%s\n",host);
        exit(1);
    }
    memcpy(&servaddr.sin_addr,ptrh->h_addr,ptrh->h_length );

    sockfd = socket (AF_INET ,SOCK_STREAM,0);
    if (sockfd < 0){
        fprintf(stderr ,"socket creation failed\n");
        exit(1);
    }

    if(connect ( sockfd,(struct sockaddr *)& servaddr,sizeof(servaddr))<0){
        fprintf( stderr,"connect failed \n");
        exit(1);
    }
    
    n = recv(sockfd,buf,sizeof(buf),0);
    while ( n>0 ){
        write(1,buf,n);
        n = recv(sockfd , buf ,sizeof(buf),0);
    }
    
    close(sockfd);

    exit(0);

}


