#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
#include <errno.h>

int main(int argc, char* argv[])
{
	pid_t newpid, wret;
	int wstatus;

	

	/*for(int i = 0; i < argc; i++)
		printf("%s ", nargv[i]);*/

	if((newpid = fork()) == -1)
	{
		perror("fork");
		exit(-1);
	}

	printf("%s\n", "-right after fork");

	if(newpid == 0) 
	{
		printf("%s %d\n", "-child!", getpid());

		char *nargv[argc-1];
		for(int i = 0; i < argc-1; i++)
			nargv[i] = argv[i+1];
		nargv[argc-1] = (char *) 0;

		execvp(argv[1], nargv);
		perror("exec"); //Если exec(2) возвратил управление, значит вызов завершился неудачей.
		//The exec() functions return only if an error has occurred. 
		//The  return value is -1, and errno is set to indicate the error.
		exit(1);
	}

	printf("%s\n", "-parent is waiting for the child");

	wret = wait(&wstatus);
	printf("%s %d\n", "-parent: wait return value: ", wret);
	printf("status value: %d\n", wstatus);
	//if WIFEXITED != 0
	
	printf("exit status: %d\n", WEXITSTATUS(wstatus));
	exit(0);	
}