#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main()
{
	printf("real user ID: %d\n", getuid());
	printf("effective user ID: %d\n", geteuid()); //uid_t getuid(void)

	FILE *file1 = fopen("myfile.txt","r"); 
	if(file1)
	{
		printf("file is oppened!\n");
		if (fclose(file1) == EOF)
    	{
        printf("%d %s", errno, strerror(errno));
        exit(-1);
    	}
		
		printf("file is closed!\n");
	}
	else
	{
		perror("file cannot be oppened\n");
	}

	if (setuid(getuid()) == -1)
    {
        printf("%d %s", errno, strerror(errno));
        exit(-1);
    }

	printf(" *effective user ID is changed* \n");	

	//again with changed ID
	printf("real user ID: %d\n", getuid());
	printf("effective user ID: %d\n",geteuid());

	FILE *file2 = fopen("myfile.txt","r");
	if(file2)
	{
		printf("file is oppened!\n");
		if (fclose(file2) == EOF)
    	{
        printf("%d %s", errno, strerror(errno));
        exit(-1);
    	}
		//fclose(file2);
		printf("file is closed!\n");
	}
	else
	{
		perror("file cannot be oppened\n");
	}
	
	exit(0);
}