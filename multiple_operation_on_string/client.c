#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h> #define PORT 8080
int main(int argc, char const *argv[])
{

    int socketR = 0, returnValue;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    socketR = socket(AF_INET, SOCK_STREAM, 0);
    if (socketR < 0)
    {

        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    //The inet_pton() function converts an Internet address in its standard text //format into its numeric binary form. The argument af specifies the family of the address.
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
    {

        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(socketR, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {

        printf("\nConnection Failed \n");
        return -1;
    }

    char buff[1024];
    int num = 0;
    bzero(buff, sizeof(buff));
    printf("Enter the String : ");
    while ((buff[num++] = getchar()) != '\n')
        ;
    send(socketR, buff, strlen(buff), 0);
    printf("Message sent to Server Succesfully - \n");
    // printf("%s", buff);

    returnValue = read(socketR, buffer, 1024);
    printf("Message Recieved from Server - \n");
    printf("%s\n", buffer);
    num = 0;
    char buff1[1024];
    bzero(buff1, sizeof(buff1));
    printf("Enter the String : ");
    while ((buff1[num++] = getchar()) != '\n')
        ;
    send(socketR, buff1, strlen(buff1), 0);
    printf("Message sent to Server Succesfully- %s\n", buff1);
    // printf("%s", buff1);

    if (strncmp("2", buff1, 1) == 0)
    {

        int i = 0;
        char secondString[1024];
        bzero(secondString, sizeof(secondString));
        printf("Enter the String : ");
        while ((secondString[i++] = getchar()) != '\n')
            ;
        send(socketR, secondString, strlen(secondString), 0);
        printf("Second String Sent- %s\n", secondString);
    }

    char buff2[1024];
    bzero(buff2, sizeof(buff2));
    returnValue = read(socketR, buff2, 1024);
    printf("Result Recieved from Server -");
    printf("%s\n", buff2);
    close(socketR);
    return 0;
}
