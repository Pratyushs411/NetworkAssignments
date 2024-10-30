#include<stdio.h>
#include<sys/socket.h>
#include<netdb.h>
#include<sys/types.h>
#include<string.h>
int main()
{
char buffer[100];
int sockid, sockid2,commfd;
struct sockaddr_in serveraddr, cliaddr;
sockid = socket(AF_INET,SOCK_STREAM,0);
serveraddr.sin_family = AF_INET;
//serveraddr.sin_addr.s_addr = inet_addr("172.16.71.87");
serveraddr.sin_addr.s_addr = INADDR_ANY; //IT WILL assign ip address
serveraddr.sin_port = htons(23456);
bind(sockid,  (struct sockaddr*)&serveraddr, sizeof(serveraddr));
listen(sockid,10);
int size = sizeof(cliaddr);
while(1){
commfd = accept(sockid, (struct sockaddr*)&cliaddr, &size);
recv(commfd,buffer,100,0);
printf("\nrecieved data %s",buffer);
send(commfd,buffer,strlen(buffer),0);
close(commfd);
}//end while
}//end main