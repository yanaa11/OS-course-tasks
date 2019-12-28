#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
	struct flock* lock_struct = malloc(sizeof(struct flock));
	int fd;
	char command[100];

	fd = open(argv[1], O_RDWR);
	if(fd == -1)
	{
		perror(argv[1]);
		free(lock_struct);
		return -1;
	}

	lock_struct->l_type = F_WRLCK; //захват по изменению
	lock_struct->l_whence = SEEK_SET; //от начала 
	lock_struct->l_start = 0; //окуда, отсчит. от whence
	lock_struct->l_len = 0; //длина захватываемоей записи, но 0 значит всю до конца 

	if(fcntl(fd, F_SETLKW, lock_struct) == -1)
	{
		if((errno == EAGAIN) || (errno == EACCES))
		{
			perror("record is locked!");
			free(lock_struct);
			return -1;
		}
		perror("fcntl");
		free(lock_struct);
		return -1;
	}

	sprintf(command, "vim %s\n", argv[1]);
	system(command);

	lock_struct->l_type = F_UNLCK;
	fcntl(fd, F_SETLK, lock_struct);
	free(lock_struct);
	close(fd);
}