#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr
void func(int sockfd)
{
char buff[MAX];
int n;
for (;;) {
bzero(buff, sizeof(buff));
printf("Enter the string : ");
n = 0;
while ((buff[n++] = getchar()) != '\n')
;
write(sockfd, buff, sizeof(buff));//send the message to server
bzero(buff, sizeof(buff)); //nullifies the buffer content
read(sockfd, buff, sizeof(buff)); //reading the message recived from server
printf("From Server : %s", buff);
if ((strncmp(buff, "exit", 4)) == 0) {
printf("Client Exit...\n");
close(sockfd);
break;
}
}
}
int main()
{
int sockfd, connfd;
struct sockaddr_in servaddr, cli;
// socket create and varification
sockfd = socket(AF_INET, SOCK_STREAM, 0);
if (sockfd == -1) {
printf("socket creation failed...\n");
exit(0);
}
else
printf("Socket successfully created..\n");
bzero(&servaddr, sizeof(servaddr));
// assign IP, PORT
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
servaddr.sin_port = htons(PORT);
// connect the client socket to server socket
if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
printf("connection with the server failed...\n");
exit(0);
}
else
printf("connected to the server..\n");
// function for chat
func(sockfd);
// close the socket
close(sockfd);
}




#include<stdlib.h>
#include<stdio.h>
#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<netdb.h>
#include<unistd.h>
int main()
{
	int sock;
	char ex[]="exit";
	char sendline[100],recvline[100];
	struct sockaddr_in servaddr;
	sock=socket(AF_INET,SOCK_STREAM,0);
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(12345);
	servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	connect(sock,(struct sockaddr *)&servaddr,sizeof(servaddr));
	while(1)
	{
		bzero(sendline,100);
		fgets(sendline,100,stdin);
		send(sock,sendline,strlen(sendline),0);
		if(strncmp(sendline,ex,4)==0)
		break;
		bzero(recvline,100);
		recv(sock,recvline,100,0);
		printf("The text received from server is:%s",recvline);
		if(strncmp(recvline,ex,4)==0)
		break;
	}
	close(sock);	
}