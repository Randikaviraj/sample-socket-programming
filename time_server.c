#include <sys/socket.h> 
#include <netinet/in.h> 
#include <strings.h> 
#include <stdio.h> 
#include <time.h>



int main(int argc, char**argv) { 
    int sockfd,n; 
    struct sockaddr_in servaddr, cliaddr; 
    socklen_t len; 
    char mesg[1000];
    time_t rawtime;
    struct tm *info;

     

    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY); 
    servaddr.sin_port=htons(32000); 


    bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr)); 

    len = sizeof(cliaddr); 

    while(1){
            n = recvfrom(sockfd,mesg,1000,0,(struct sockaddr *)&cliaddr,&len);
            while(1){
                rawtime=time(NULL);
                info = localtime( &rawtime );
                sendto(sockfd,asctime(info),sizeof(asctime(info)),0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
                sleep(1);
            } 
            
    }
 

    return 0; 


}