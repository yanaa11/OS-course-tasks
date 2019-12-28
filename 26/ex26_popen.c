#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main()
{
	FILE *fptr;
    char *line = "Hello, world!";

	if((fptr = popen("./26read", "w")) == (FILE*)NULL)
	{
		perror("popen");
		exit(-1);
	}

    fputs(line, fptr);
    int estat;

    if((estat = pclose(fptr)) == -1)
    {
    	perror("pclose");
    	exit(estat);
    }

    if (WIFEXITED(estat))
    {
    	printf("%d\n", WEXITSTATUS(estat));
   		exit(WEXITSTATUS(estat));
    }

    else
    {
    	exit(-1);
    }
    
}