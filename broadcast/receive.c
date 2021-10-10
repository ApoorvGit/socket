#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define MAX 80
#define PORT 43454
#define SA struct sockaddr

int main()
{
    char buff[MAX];
    int sockfd, len, n;
    struct sockaddr_in servaddr;
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1)
    {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(len));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY; //inet_addr("192.168.43."); servaddr.sin_port=htons(PORT);

    if ((bind(sockfd, (SA *)&servaddr, sizeof(servaddr))) != 0)
    {
        printf("socket bind failed...\n");
        exit(0);
    }
    len = sizeof(servaddr);

    recvfrom(sockfd, buff, sizeof(buff), 0, (SA *)&servaddr, &len);
    printf("Message Recieved : %s\n", buff);

    close(sockfd);
}
