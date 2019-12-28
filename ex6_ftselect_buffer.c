#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/mman.h>

int main(int argc, char* argv[])
{
	typedef struct 
	{
		int fd; //file descriptor
		size_t lines;
		size_t line_len[500];
		size_t file_size;
		char* displ[500];
	} table;

	table* f_table = (table*) malloc(sizeof(table));
	char* file_buffer;

	f_table->fd = open(argv[1], O_RDONLY);
	if(f_table->fd == -1)
	{
		perror("Can't open file");
		free(f_table);
		return -1;
	}

	f_table->file_size = lseek(f_table->fd, 0, 2); //узнаем длину файла, 2 - поставить в конец
	printf("%ld\n", f_table->file_size);
	lseek(f_table->fd, 0, 0);
	file_buffer = (char*)malloc(f_table->file_size);
	if(file_buffer == NULL) perror("Malloc ");
	int r;
	if(r = read(f_table->fd, file_buffer, f_table->file_size) == -1)
	{
		perror("Can't read file");
		free(f_table);
		return -1;
	}   
	if(r < f_table->file_size) printf("%s\n", "Not all file was read");
	printf("%d\n", r);
	if(close(f_table->fd) == 1) perror("Troubles with file closing");

	f_table->displ[0] = NULL; //чтобы не заморачиваться с индексами, т.к. строки считаются с 1
	f_table->displ[1] = file_buffer; //указатель на начало первой строчки

	f_table->lines = 1;
	size_t place = 0;
	size_t len = 1;

	for(place = 0; place < f_table->file_size; place++)
	{
		if(*(file_buffer + place) == '\n')
		{
			f_table->line_len[f_table->lines] = len; //на каждой новой строчке заново насчитываем ее длину посимвольно
			f_table->lines++;
			f_table->displ[f_table->lines] = file_buffer + place + 1; //уже смотрим на начало следующей строчки
			len = 1; //"сбрасываем" считалку длины для следующей строки
		}
		else len++; //насчитываем длину строчки посимвольно
	}
	f_table->lines--; //потому что делаем это в цикле лишний раз

	printf("%s", "   Lines in file: " );
	printf("%ld\n", f_table->lines);

	size_t line_number;

	struct timeval tv;
	fd_set rdfds;

	do
	{
		fflush(stdout);

		tv.tv_sec = 5;
		tv.tv_usec = 0;
		
		FD_ZERO(&rdfds);
		FD_SET(0, &rdfds); //0 - стандартный поток ввода

		printf("%s\n", "   Enter line number fast: ");
		int retval = select(1, &rdfds, NULL, NULL, &tv);
		if (retval == -1)
        	perror("Select");
        else if (retval)
        {
			scanf("%ld", &line_number);
			if(line_number < 0)
				{printf("%s\n", "   Wrong line number");}
			else if(line_number > 0)
			{
				if (line_number > f_table->lines) 
					{printf("%s\n", "   Wrong line number");} 
				else
				{
					write(1, f_table->displ[line_number], f_table->line_len[line_number]);
					
				}
			}
		}
		else
		{
			printf("   No number within five seconds. Here your file:\n");
        	write(1, f_table->displ[1], f_table->file_size);
        	printf("%s\n", "   Bye!");
        	free(file_buffer);
			free(f_table);
			return 0;			
		}
	}
	while(line_number > 0);

	free(file_buffer);
	free(f_table);
	return 0;

}


