#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <stdio.h> 
#include <string.h>
int main(int argc, char**argv){ 
    int sockfd,n; 
    struct sockaddr_in servaddr; 
    char sendline[1000],a[10];
    char recvline[1000]; 


    
    sockfd=socket(AF_INET,SOCK_DGRAM,0); 
    bzero(&servaddr,sizeof(servaddr));


    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr=INADDR_ANY; 
    servaddr.sin_port=htons(32000); 

    
    sendto(sockfd,"connect",strlen("connect"),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
   

    while(1){
        n=recvfrom(sockfd,recvline,10000,0,NULL,NULL); 
        recvline[n]=0; 
        printf("Received: %s\n",recvline);
    }

     
     return 0; 
}