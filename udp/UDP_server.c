#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
  

#define MAXLINE 40
  


int main(int argc,char* argv[]) {
    int sockfd;
    char buffer[MAXLINE];
    char *hello = "Server answer";
    struct sockaddr_in servaddr, cliaddr;
	int reuse = 1;
      
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    char* servHost = (char*)malloc(20);
    int servPort;
    printf("Server port : ");
    scanf("%d",&servPort);
    printf("Server address : ");
    scanf("%s",servHost);
 
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));
      
    servaddr.sin_family    = AF_INET; 
    servaddr.sin_addr.s_addr = inet_addr(servHost);
    servaddr.sin_port = htons(servPort);
	
    
    if ( bind(sockfd, (struct sockaddr *)&servaddr, 
            sizeof(servaddr)) < 0 )
    {
        perror("bind failed");
        exit(1);
    }
     
    socklen_t len;
	int n;
  
    len = sizeof(cliaddr);
	while(1){
		n = recvfrom(sockfd, (char *)buffer, MAXLINE, 0, ( struct sockaddr *)&cliaddr, &len);
		buffer[n] = '\0';

		printf("Client request IP =  %s\n",inet_ntoa(((struct sockaddr_in*)&cliaddr)->sin_addr));
		sendto(sockfd, (char *)hello, strlen(hello), 0, (struct sockaddr *)&cliaddr, len);
		
	}
    return 0;
}
