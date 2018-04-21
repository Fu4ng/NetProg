#include<sys/types.h>
#include<unistd.h>
#include<error.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netdb.h>
#include<netinet/in.h>
//中断处理过程
//void int_proc(int signo){ }

int main(int argc ,char **argv){
    struct sockaddr_in daddr,sdaddr,cmpaddr;
    int sockfd;
    int timer = 3;
    char buffer[1024];
    int addrlen,n;

    //判断用户输入的命令行是否正确，如果有错，提示用法
    if(argc != 5){
        printf("用法:%s 目的IP 目的端口 源IP 源端口\n",argv[0]);
        exit(1);
    }
    //设定中断处理函数 并设置时间限制
  //  signal(SIGALRM,int_proc);
   // alarm(timer);

    //建立数据报套接字
    sockfd  =socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd<0){
        fprintf(stderr,"socket error!\n");
        exit(1);
    }
    //为结构变量daddr的各个字段赋值
    addrlen = sizeof(struct sockaddr_in);
    memset(&daddr,0,addrlen);
    daddr.sin_family = AF_INET;
    daddr.sin_port = htons(atoi(argv[2]));
    if(inet_pton(AF_INET,argv[1],&daddr.sin_addr)<=0){
        fprintf(stderr,"Invaild dest IP \n");
        exit(1);
    }
    //为结构变量saddr的各个字段赋值
    addrlen = sizeof(struct sockaddr_in );
    memset(&sdaddr,0,addrlen);
    sdaddr.sin_family=AF_INET;
    sdaddr.sin_port = htons(atoi(argv[4]));
    if(inet_pton(AF_INET,argv[3],&sdaddr.sin_addr)<=0){
        fprintf(stderr,"Invaild source IP\n");
        exit(1);
    }
    
    //绑定地址
    if(bind(sockfd,&sdaddr,addrlen)<0){
        fprintf(stderr,"bind local addr error!\n");
        exit(2);
    }
    if(fgets(buffer,1024,stdin)==NULL) exit(0);
    if(sendto(sockfd,buffer,strlen(buffer),0,&daddr,addrlen)<=0){

        fprintf(stderr,"sendto error!\n");
        exit(2);
    }
    while(1){
        //接受信息并显示
        n=recvfrom(sockfd,buffer,1024,0,&cmpaddr,&addrlen );
        if(n<0){
/*             if(errno == EWOULDBLOCK)
                fprintf(stderr,"recvfrom timeout error!\n");
            else{
                fprintf(stderr," recvfrom error!\n");
                exit(3);
               }
*/      
            fprintf(stderr,"recv err!!!\n");
        }
        else{                    
            if(memcmp(&cmpaddr,&daddr,addrlen)) continue;
            buffer[n]=0;         
            printf("Received:%s",buffer);    
            }
        if(fgets(buffer,1024,stdin)==NULL) exit(0);
        if(sendto(sockfd,buffer,strlen(buffer),0,&daddr,addrlen)<=0){
            fprintf(stderr,"sendto error!\n");
            exit(3);
        }
    }
    close(sockfd);
}











