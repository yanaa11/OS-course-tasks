#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


int main()
{
	char buffer[1000];
	int i;
	int rtn; 

	while ((rtn = read(0, buffer, 1000)) > 0) 
	{
		for(i = 0; i < rtn; i++)
		if(islower(buffer[i]))
		buffer[i] = toupper(buffer[i]);
		write(1, buffer, rtn);
		write(1, "\n", 1);

	}
	exit(10);
}