
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<arpa/inet.h>
#include<unistd.h>
int main()
{
char buff[80];
int sockfd,len,n;
struct sockaddr_in servaddr;
sockfd=socket(AF_INET,SOCK_DGRAM,0);
if(sockfd==-1)
{
printf("socket creation failed...\n");
exit(0);
}
else
printf("Socket successfully created..\n");
bzero(&servaddr,sizeof(len));
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
servaddr.sin_port=htons(43454);
len=sizeof(servaddr);
while(1){
printf("\nEnter string : ");
n=0;
while((buff[n++]=getchar())!='\n');//getting buffer ,can use fget also fgets(buff,sizeof(buf),stdin);
sendto(sockfd,buff,strlen(buff),0,(struct sockaddr *)&servaddr,len);
bzero(buff,sizeof(buff));
len=sizeof(servaddr);
recvfrom(sockfd,buff,sizeof(buff),0,(struct sockaddr *)&servaddr,&len);

printf("From Server : %s\n",buff);
}

close(sockfd);
}
