#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h> #define PORT 8080
int main(int argc, char const *argv[])
{

    int serFileDescriptor, newSocket, returnValue;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char r[1000];
    int opt = 1;
    serFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    //Here 0 parameter in socket System call defines the Protocol Type if(serFileDescriptor == 0)
    {

        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(serFileDescriptor, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {

        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT); //host to network byte ordering - little ending / big
    ending
        //The htons function takes a 16-bit number in host byte order and returns a
        //16-bit number in network byte order used in TCP/IP networks (the AF_INET or AF_INET6 address family).

        int temp = bind(serFileDescriptor, (struct sockaddr *)&address, sizeof(address));
    if (temp < 0)
    {

        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(serFileDescriptor, 3) < 0)
    //Here 3 defines the Queue length of server waiting for Clients
    {

        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((newSocket = accept(serFileDescriptor, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
    {

        perror("accept");
        exit(EXIT_FAILURE);
    }

    char inputString[1024];
    char selected[1024];
    bzero(inputString, sizeof(inputString));
    returnValue = read(newSocket, inputString, 1024);
    printf("Client's Message -");
    printf("%s", inputString);

    char operation[] = { "Specifiy the Operation -\n 1: Sorting\n 2: Comparison\n 3: Copy\n 
                         4 : Insertion\n 5 : Deletion "}; send(newSocket, operation, strlen(operation), 0); printf(" Message Sent Succesfully\n "); 
                         bzero(selected, sizeof(selected));
    returnValue = read(newSocket, selected, 1024);
    printf("Client's Message -");
    printf("%s", selected);

    //Sorting Operation
    if (strncmp("1", selected, 1) == 0)
    {

        printf("Operation Selected - Sorting\n");
        char temp;
        int i, j;
        int n = strlen(inputString);
        for (i = 0; i < n - 1; i++)
        {
            for (j = i + 1; j < n; j++)
            {
                if (inputString[i] > inputString[j])
                {
                    temp = inputString[i];
                    inputString[i] = inputString[j];
                    inputString[j] = temp;
                }
            }
        }

        send(newSocket, inputString, strlen(inputString), 0);
        printf("Message Sent to Client after Sorting Operation- %s\n", inputString);
    } //Comparison Operation else if(strncmp("2", selected, 1) == 0)
    {

        printf("Operation Selected - Comparison\n");
        int value;
        char stringComp[1024];
        bzero(stringComp, sizeof(stringComp));
        returnValue = read(newSocket, stringComp, 1024);
        printf("Second String -");
        printf("%s", stringComp);
        value = strcmp(inputString, stringComp);
        if (value == 0)
        {

            printf("Strings are Same\n");
            char result[] = {"Both Strings are Same"};
            send(newSocket, result, strlen(result), 0);
            printf("Message Sent to Client after Comparison Operation %s\n -", result);
        }

        else
        {

            printf("Strings are different\n");
            char result[] = {"Both Strings are Different"};
            send(newSocket, result, strlen(result), 0);
            printf("Message Sent to Client after Comparison Operation %s\n -", result);
        }

    } //Copy Operation
    else if (strncmp("3", selected, 1) == 0)
    {

        printf("Operation Selected - Copy\n");
        char *copiedString;
        copiedString = (char *)malloc(100);
        strcpy(copiedString, inputString);
        printf("String Copied \n");
        char result[] = {"String Copied"};
        send(newSocket, result, strlen(result), 0);
        printf("Copied String is: %s\n", copiedString);
    } //Exit if No Operation Selected else
    {

        printf("Connection Terminated\n");
    }

    close(newSocket);
    close(serFileDescriptor);
    return 0;
}
