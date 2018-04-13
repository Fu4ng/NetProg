#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<stdio.h>
#include<string.h>

#define PROTOPORT 5188

extern int errno;

char localhost[] = "0.0.0.0";

main(int argc,char *argv[])
{
	struct hostent *ptrh;
	struct sockaddr_in servaddr;
}
