#include <stdio.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#define MAX 80
#define PORT 43454
#define SA struct sockaddr

int main()
{
    int sockfd;
    struct sockaddr_in servaddr, cli;
    char buff[] = "This is a broadcast Message";
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    int broadcastPermission = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, (void *)&broadcastPermission, sizeof(broadcastPermission));
    if (sockfd == -1)
    {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("192.168.43.255");
    servaddr.sin_port = htons(PORT);
    printf("\n Sending Broadcast");
    sendto(sockfd, buff, sizeof(buff), 0, (SA *)&servaddr, sizeof(servaddr));
    printf("\n ....... sent");
    close(sockfd);
}
