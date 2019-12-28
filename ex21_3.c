#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>      
#include <sys/time.h>
#include <sys/types.h>
#include <fcntl.h>

int count = 0;
int fdsig[2];


int main()
{
	if(pipe(fdsig) == -1)
	{
		perror("pipe");
		exit(-1);
	}

	void sigcatch(int);

	if(signal(SIGINT, sigcatch) == SIG_ERR)
	{
		perror("signal SIGINT");
		exit(-1);	
	}

	if(signal(SIGQUIT, sigcatch) == SIG_ERR)
	{
		perror("signal SIGQUIT");
		exit(-1);
	}

	char s;
	fd_set rfds;

	FD_ZERO(&rfds);
	FD_SET(fdsig[0], &rfds);
	int r;
	int retval;
	int nfd = fdsig[0] + 1;
	max_fd = ...
	printf("%s\n", "ready!");

	//---------------------ОСНОВНОЙ ЦИКЛ

	while(1)
	{
		printf("%s\n", "before select");
		retval = select(max_fd + 1, &rfds, NULL, NULL, NULL);

		r = read(fdsig[0], &s, 1);
		printf(" r:%d ", r);
		printf(" %c ", s); 	

		if(s == 'Q')
		{
			printf(" count:%d\n", count); 
			exit(0);
		}

		if(s == 'I')
		{
			count++;
			printf("%c . ", '\a'); //оно не пищит ((((
			printf("%s\n", "beep");
		}

	}

}


void sigcatch(int sig)
{
	signal(sig, SIG_IGN); //чтобы не прерваось по приходу нового сигнала, пока обрабатываем первый
	char buf;

	if(sig == SIGQUIT) 
	{
		buf = 'Q';
		write(fdsig[1], &buf, 1);
		//printf(" %s ", "in SIGQUIT");
	}
	
	if(sig == SIGINT)
	{
		//printf(" %s ", "in SIGINT before write");
		buf = 'I';
		write(fdsig[1], &buf, 1);
		//printf(" %s ", "after write");
	}

	signal(sig, sigcatch); 
	/*потому что после одного срабатывания signal реакция на сиглал сбростся на дефолтную*/
}