#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	int sock;
	struct sockaddr_un server;

	if (argc < 3) 
	{
		printf("bad args!");
		exit(-1);
	}

	sock = socket(AF_UNIX, SOCK_STREAM, 0);
	if (sock < 0) 
	{
		perror("opening socket");
		exit(-1);
	}
	
	memset(&server, 0, sizeof(struct sockaddr_un));
    /* Clear structure */

	server.sun_family = AF_UNIX;
	strcpy(server.sun_path, argv[1]);

	/* The  connect()  system call connects the socket referred to by the file
       descriptor sockfd to the address specified by addr. */

	if (connect(sock, (struct sockaddr *) &server, sizeof(struct sockaddr_un)) < 0) 
	{
		close(sock);
		perror("connecting socket");
		exit(-1);
	}
	
	if (write(sock, argv[2], sizeof(argv[2])) < 0)
		perror("writing on socket");
	
	close(sock);
}