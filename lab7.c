#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 5000
#define MAXLINE 1024

int main() {
    int listenfd, connfd, udpfd, maxfd;
    char buffer[MAXLINE];
    fd_set readfds;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len;
    ssize_t n;

    // Initialize the server address structure
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Create TCP socket
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    listen(listenfd, 10);

    // Create UDP socket
    udpfd = socket(AF_INET, SOCK_DGRAM, 0);
    bind(udpfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

    // Find the maximum file descriptor
    maxfd = (listenfd > udpfd ? listenfd : udpfd) + 1;

    while (1) {
        // Clear and set file descriptors
        FD_ZERO(&readfds);
        FD_SET(listenfd, &readfds);
        FD_SET(udpfd, &readfds);

        // Wait for activity on either TCP or UDP socket
        select(maxfd, &readfds, NULL, NULL, NULL);

        // Handle TCP connections
        if (FD_ISSET(listenfd, &readfds)) {
            len = sizeof(cliaddr);
            connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &len);  88888888888888888
            if (fork() == 0) {  // Child process
                close(listenfd);  // Close the listening socket in child process
                while (1) {
                    memset(buffer, 0, sizeof(buffer));
                    read(connfd, buffer, sizeof(buffer));  // Read from TCP client
                    printf("Message from TCP client: %s\n", buffer);

                    fgets(buffer, sizeof(buffer), stdin);  // Server input to reply
                    write(connfd, buffer, strlen(buffer));  // Reply to TCP client
                }
                close(connfd);  // Close the connection
                exit(0);  // Child process exits
            }
            close(connfd);  // Parent process closes its copy of connfd
        }

        // Handle UDP messages
        if (FD_ISSET(udpfd, &readfds)) {
            len = sizeof(cliaddr);
            memset(buffer, 0, sizeof(buffer));
            n = recvfrom(udpfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&cliaddr, &len);
            printf("Message from UDP client: %s\n", buffer);

            fgets(buffer, sizeof(buffer), stdin);  // Server input to reply
            sendto(udpfd, buffer, strlen(buffer), 0, (struct sockaddr*)&cliaddr, len);  // Reply to UDP client
        }
    }

    return 0;
}
SERVER ka code hai yeh select wala