#include <sys/socket.h> 
#include <netinet/in.h> 
#include <strings.h> 
#include <stdio.h> 
#include <ctype.h> 
#include <string.h>



int main(int argc, char**argv) { 
    int sockfd,n,temp,j; 
    struct sockaddr_in servaddr, cliaddr,temp_client; 
    socklen_t len,temp_len; 
    char mesg[1000];

    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY); 
    servaddr.sin_port=htons(32000); 


    bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr)); 

    len = sizeof(cliaddr); 

    while(1){
            n = recvfrom(sockfd,mesg,1000,0,(struct sockaddr *)&cliaddr,&len); 
            mesg[n]=0;
            n=atoi(mesg);
            if(n){
                sendto(sockfd,"ACK\n",4,0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
            }else{
                sendto(sockfd,"FAILED",6,0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
                continue;
            }
            
            while(n>0){
                bzero(&temp_client,sizeof(temp_client));
                temp_len = sizeof(temp_client);
                temp=recvfrom(sockfd,mesg,1000,0,(struct sockaddr *)&temp_client,&temp_len);
                if(temp_client.sin_addr.s_addr==cliaddr.sin_addr.s_addr && temp_client.sin_port==cliaddr.sin_port){

                    j=0;
                    while (mesg[j]) { 
                        mesg[j] = toupper(mesg[j]); 
                        j++; 
                    } 
                    mesg[j]=0;
                    sendto(sockfd,mesg,temp,0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));

                    n--;
                }else{
                    sendto(sockfd,"BUSY",4,0,(struct sockaddr *)&temp_client,sizeof(temp_client));
                }
            }
            
    }
 

    return 0; 


}

