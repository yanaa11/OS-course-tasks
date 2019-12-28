#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define NAME "mysocket1"

 /*Sockets  of type SOCK_STREAM are full-duplex byte streams.  They do not
 preserve record boundaries.  A stream socket must  be  in  a  connected
 state  before  any data may be sent or received on it.  A connection to
 another socket is created with a connect(2) call. */

int main()
{
	int sock, msgsock, rval;
	struct sockaddr_un server;
	char buf[1024];

	/* int socket(int domain, int type, int protocol); 
	The domain argument specifies a communication domain; this selects  the 
	protocol  family  which will be used for communication. The  socket  has  the indicated type, which specifies the communication
    semantics. The protocol specifies a  particular  protocol  to  be  used  with  the
    socket.  Normally only a single protocol exists to support a particular
    socket type within a given protocol family, in which case protocol  can be  specified  as  0.

	*/

	sock = socket(AF_UNIX, SOCK_STREAM, 0);
	if (sock < 0) 
	{
		perror("opening socket");
		exit(-1);
	}

 	memset(&server, 0, sizeof(struct sockaddr_un));
    /* Clear structure */


	server.sun_family = AF_UNIX;
	strcpy(server.sun_path, NAME);

	/*привязать сокет к адресу - сделать из него серверный - слушать и принимать соединения.
	для клиентского bind не обзателен

	int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

	When  a  socket  is  created  with socket(2), it exists in a name space
    (address family) but has no address assigned to it.  bind() assigns the
    address  specified  by  addr  to  the  socket  referred  to by the file
    descriptor sockfd.  addrlen  specifies  the  size,  in  bytes,  of  the
    address structure pointed to by addr. 

	*/


	if (bind(sock, (struct sockaddr*) &server, sizeof(struct sockaddr_un)) < 0) 
	{
		perror("binding socket");
		close(sock);
		exit(-1);
	}

	printf("Server's socket name: %s\n", server.sun_path);
	listen(sock, 1); /*The backlog argument defines the maximum length to which the  queue  of
       pending  connections  for  sockfd  may  grow. */

	/* The  accept()  system  call  is used with connection-based socket types
       (SOCK_STREAM,  SOCK_SEQPACKET).   It  extracts  the  first   connection
       request  on  the queue of pending connections for the listening socket,
       sockfd, creates a new connected socket, and returns a new file descrip‐
       tor  referring  to that socket.  The newly created socket is not in the
       listening state.  The original socket  sockfd  is  unaffected  by  this
       call.

       The  argument  sockfd is a socket that has been created with socket(2),
       bound to a local address with bind(2), and is listening for connections
       after a listen(2).*/

	msgsock = accept(sock, 0, 0);

	if (msgsock == -1)
		perror("accept");

	else
	{	
		if ((rval = read(msgsock, buf, 1024)) < 0)
			perror("reading stream message");

		else
		{
			int i =0;
			for(i=0; i < rval; i++)
				if(islower(buf[i]))
					buf[i] = toupper(buf[i]);

			printf("%s\n", buf);
		}

	}

	close(msgsock);

	close(sock);
	unlink(NAME);
}