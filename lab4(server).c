#include <stdio.h>
#include <signal.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr
// Function designed for chat between client and server.
void func(int sockfd, short cport)
{
char buff[MAX];
int n;

// infinite loop for chat
for (;;) {
    bzero(buff, MAX); // set buff with null values
// read the message from client and copy it in buffer
    read(sockfd, buff, sizeof(buff));
	//recvfrom
// print buffer which contains the client contents
    printf("From client(%d): %s\nTo client(%d) : ",cport, buff,cport);
    bzero(buff, MAX);
    n = 0;
 // copy server message in the buffer
    while ((buff[n++] = getchar()) != '\n')
      ;
// and send that buffer to client
    write(sockfd, buff, sizeof(buff));
	//sendto
// if msg contains "Exit" then server exit and chat ended.
   if (strncmp("exit", buff, 4) == 0) {
    printf("Server Exit...\n");
   break;
   }
}
}



// Driver function
int main()
{
int sockfd, connfd, len;
struct sockaddr_in servaddr, cli;
pid_t pid;
unsigned short c_port;

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
servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
servaddr.sin_port = htons(PORT);



// Binding newly created socket to given IP and verification
if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
printf("socket bind failed...\n");
exit(0);
}
else
printf("Socket successfully binded..\n");
// Now server is ready to listen and verification
if ((listen(sockfd, 5)) != 0) {
printf("Listen failed...\n");
exit(0);
}
else
printf("Server listening..\n");
len = sizeof(cli);


while(1){
// Accept the data packet from client and verification
connfd = accept(sockfd, (SA*)&cli, &len);
if (connfd < 0) {
printf("server acccept failed...\n");
exit(0);
}
else{
printf("server acccept(%d) the client...\n",connfd);
c_port= ntohs(cli.sin_port);


pid = fork();

if(pid==0)
    {
close(sockfd);
// Function for chatting between client and server	
func(connfd,c_port);
   }
  }//end else
}//end while(1)

close(sockfd);
}





#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<unistd.h>
int main()
{
	int listen_fd,comm_fd;
	char str[100];
	char ex[]="exit";
	struct sockaddr_in servaddr;
	listen_fd=socket(AF_INET,SOCK_STREAM,0);
	servaddr.sin_port=htons(12345);
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=INADDR_ANY;
	bind(listen_fd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	listen(listen_fd,10);
	comm_fd=accept(listen_fd,(struct sockaddr *)NULL,NULL);
	while(1)
	{
		bzero(str,100);
		recv(comm_fd,str,100,0);
		printf("Received from cleint:%s",str);
		if(strncmp(str,ex,4)==0)
		break;
		bzero(str,100);
		fgets(str,100,stdin);
		send(comm_fd,str,strlen(str),0);
		if(strncmp(str,ex,4)==0)
		break;
	}
	close(comm_fd);
	close(listen_fd);
	
	
	
}