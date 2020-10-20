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

    printf("Enter the no of sentences :");
    scanf("%s",a);
    sendto(sockfd,a,strlen(a),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
    n=recvfrom(sockfd,recvline,10000,0,NULL,NULL); 
    recvline[n]=0; 
    printf("Received: %s\n",recvline);
    
    if(!strcmp(recvline,"FAILED")){
        printf("Connection failed");
        return -1;
    }

    for(int i=0;i<atoi(a);i++){
        printf("Enter the next sentence (%d): \n",i);
        scanf("\n");
        scanf("%[^\n]%*c",sendline);
        sendto(sockfd,sendline,strlen(sendline),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
        n=recvfrom(sockfd,recvline,10000,0,NULL,NULL); 
        recvline[n]=0; 
        printf("Received: %s\n",recvline);
    }

     
     return 0; 
    }