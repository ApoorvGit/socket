// Server C code to reverse a
// string by sent from client
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8090

// Driver code
int main()
{
	int server_fd, new_socket, valread;
	struct sockaddr_in address;
	char str[100];
	int addrlen = sizeof(address);
	char buffer[1024] = { 0 };
	char* hello = "Hello from server";

	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET,
						SOCK_STREAM, 0)) == 0) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	// Forcefully attaching socket to
	// the port 8090
	if (bind(server_fd, (struct sockaddr*)&address,
						sizeof(address)) < 0) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	// puts the server socket in passive mode
	if (listen(server_fd, 3) < 0) {
		perror("listen");
		exit(EXIT_FAILURE);
	}
	if ((new_socket = accept(server_fd,
				(struct sockaddr*)&address,
				(socklen_t*)&addrlen)) < 0) {
		perror("accept");
		exit(EXIT_FAILURE);
	}

	// read string send by client
	valread = read(new_socket, str,
				sizeof(str));
	int i, j, temp;
	int l = strlen(str);

	printf("\nString sent by client:%s\n", str);

	// loop to reverse the string
	for (i = 0, j = l - 1; i < j; i++, j--) {
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
	}

	// send reversed string to client
	// by send system call
	send(new_socket, str, sizeof(str), 0);
	printf("\nModified string sent to client\n");

	return 0;
}
