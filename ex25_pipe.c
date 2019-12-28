#include <unistd.h>
#include <sys/types.h>       
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h> 
#include <ctype.h>



int main(int argc, char *argv[])
{
	int pipefd[2];
	pid_t cpid;
	int i, rtn;

	static char *line = "Hello world!";
	char buf[1000];

	if(pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(-1);
	}

	cpid = fork();

	if(cpid == -1)
	{
		perror("fork");
		close(pipefd[0]);
		close(pipefd[1]);
		exit(-1);
	}

	if(cpid == 0)
	{
		//child
		if(close(pipefd[1]) == -1)
		{
			perror("pipefd[1] in rd");
		} 
		while ((rtn = read(pipefd[0], buf, 1000))> 0) 
		{
			for(i=0; i < rtn; i++)
			if(islower(buf[i]))
				buf[i] = toupper(buf[i]);
			write(1, buf, rtn);
			write(1, "\n", 1);
 		}

		if(close(pipefd[0]) == -1)
		{
			perror("pipefd[0]");
		}
		exit(0);
	} 

	else	
	{
		//parent
		close(pipefd[0]); /* close unused read end */
		write(1, line, strlen(line));
		write(1, "\n", 1);
		write(pipefd[1], line, strlen(line));
		//write(pipefd[1], argv[1], strlen(argv[1])); 
		if(close(pipefd[1]) == -1)
		{
			perror("pipefd[1]");
		}
		wait(NULL);
		exit(0);
	}

}