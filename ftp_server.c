#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

int main(){
    FILE *fp;
    char str_data[1000],recvline[1000];
    char ch;
    int server_socket,client_socket,i,n;
    struct sockaddr_in server_address;

    
    
    server_socket=socket(AF_INET,SOCK_STREAM,0);

    server_address.sin_family=AF_INET;
    server_address.sin_port=htons(32000);
    server_address.sin_addr.s_addr=htonl(INADDR_ANY);

    bind(server_socket,(struct sockadder*)&server_address,sizeof(server_address));

    listen(server_socket,0);

    while(1){
        client_socket=accept(server_socket,NULL,NULL);
        n=recvfrom(client_socket,recvline,1000,0,NULL,NULL);
        recvline[n]=0; 
        fp = fopen("serverfile.txt","r");

        if (fp == NULL)
        {
            perror("Error while opening the file.\n");
            send(client_socket,"Failure in server",sizeof("Failure in server"),0);
            continue;
        }

        send(client_socket,"47",sizeof("47"),0);

        i=0;
        bzero(str_data,1000);

        while((ch = fgetc(fp)) != EOF){
            str_data[i]=ch;
            if(i==998){
                str_data[999]=0;
                send(client_socket,str_data,sizeof(str_data),0);
                i=0;
                bzero(str_data,1000);
            }
            i++;

        }
        str_data[i]=0;
        send(client_socket,str_data,sizeof(str_data),0);
        fclose(fp);
    }
    
    return 0;
}