#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main()
{
	for (int i = 0; i < 2; i++) 
	{
		printf("RID = %d\n",(uid_t) getuid());
		printf("EUID = %d\n",(uid_t) geteuid());

		FILE *file = fopen("myfile.txt","r");
		if(file){
			fclose(file);
			printf("Ok\n");
		}
		else
		{
			perror("This file doesn`t open\n");
		}
		
		if (i == 0)
			printf("%i\n",setuid(getuid()));
		}
	exit(0);
}