#include <sys/socket.h> 
#include <stdlib.h>
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <stdio.h> 
#include <string.h>
int main(int argc, char**argv){ 
    FILE *fptr;
    int sockfd,n,noofb; 
    struct sockaddr_in servaddr; 
    char sendline[1000],a[10];
    char recvline[1000]; 


    
    sockfd=socket(AF_INET,SOCK_STREAM,0); 
    bzero(&servaddr,sizeof(servaddr));


    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr=INADDR_ANY; 
    servaddr.sin_port=htons(32000); 

    fptr = fopen("client_program.txt", "w");

    if (fptr == NULL) {
        printf("Error!");
        exit(1);
    }


    connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)); 
    sendto(sockfd,"request",strlen("request"),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
    n=recvfrom(sockfd,recvline,10000,0,NULL,NULL);
    recvline[n]=0;
    printf("Received data size: %s\n",recvline);
    
    noofb=atoi(recvline);
    noofb=noofb/1000+1;
    
    if(!noofb){
        printf("Error!");
        exit(1);
    }
    

    int i=0;
    while(i<noofb){
        n=recvfrom(sockfd,recvline,10000,0,NULL,NULL); 
        recvline[n]=0; 
        fputs(recvline, fptr);
        i++;
    }

     fclose(fptr);
     
     return 0; 
}