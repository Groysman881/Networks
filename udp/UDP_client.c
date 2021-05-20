#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>

int main(int argc,char* argv[]){

	int broadcast = 1;
	int servPort;
	char hostBuffer[256];
	struct hostent *host_entry;
	int cliPort;
	char* servAddr = (char*)malloc(20);
	printf("Client port : ");
	scanf("%d",&cliPort);
	printf("Server port : ");
	scanf("%d",&servPort);
	printf("Server address : ");
	scanf("%s",servAddr);
	int hostname = gethostname(hostBuffer,sizeof(hostBuffer));
	host_entry = gethostbyname(hostBuffer);
	struct sockaddr_in server,client;
	memset(&client,0,sizeof(client));
	client.sin_family = AF_INET;
	client.sin_addr = *(struct in_addr*)host_entry->h_addr_list[0];
	client.sin_port = htons(cliPort);
	struct sockaddr from;
	int sock = socket(AF_INET,SOCK_DGRAM,0);
	fcntl(sock,F_SETFL,O_NONBLOCK);
	if(sock < 0){
		perror("socket\n");
		exit(1);
	}
	memset(&server,0,sizeof(server));

	if(setsockopt(sock,SOL_SOCKET,SO_BROADCAST,&broadcast,sizeof(broadcast)) ==
	-1){
		perror("setsockopt(SO_BROADCAST");
		exit(1);		
	}
	
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(servAddr);
	server.sin_port = htons(servPort);

	int rc = bind(sock,(struct sockaddr*)&client,sizeof(client));
	if(rc < 0){
		printf("%s : cannot bind port number %d \n",argv[0],cliPort);
		exit(1);
	}
	char buf[81];	

	socklen_t len;
	int n;
	len = sizeof(from);
	while(1){
		memset(buf,'\0',81);
		strcpy(buf,"CLIENT lookup");
		printf("Send!\n");
		if(sendto(sock,&buf,strlen(buf),0,(struct sockaddr*)&server,sizeof(server)) < 0){
			perror("sendto");
			exit(1);
		}
		sleep(10);
		memset(buf,0,81);
		strcpy(buf,"\0");
		printf("%s\n",buf);
		
		n = recvfrom(sock,buf,80,0,&from,&len);
		if(n > 0){			
			break;
		}
	}
	printf("SERVER found IP %s\n",inet_ntoa(((struct sockaddr_in*)&from)->sin_addr));
	close(sock);
	return 0;
}
