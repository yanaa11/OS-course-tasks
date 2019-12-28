#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char* argv[])
{
	typedef struct 
	{
		int fd; //file descriptor
		size_t lines;
		size_t line_len[500];
		size_t line_offset[500];
	} table;

	table* f_table = (table*) malloc(sizeof(table));

	char ch, buffer[257];

	f_table->fd = open(argv[1], O_RDONLY);
	if(f_table->fd == -1)
	{
		printf("%s\n", "can't open file");
		free(f_table);
		return -1;
	}

	f_table->line_len[0] = 0; //чтобы не заморачиваться с индексами, т.к. строки считаются с 1
	f_table->line_offset[0]  = 0;
	f_table->line_offset[1] = 0; //смещение для самой первой строчки

	f_table->lines = 1;
	size_t place = 0;

	while(read(f_table->fd, &ch, 1)) //читаем по одному символу, позиция в файле смещается
	{
		if(ch == '\n')
		{
			place++;
			f_table->line_len[f_table->lines] = place;
			f_table->lines++;
			f_table->line_offset[f_table->lines] = lseek(f_table->fd, 0, 1);
			place = 0;
		}
		else place++;
	}
	f_table->lines--;

	printf("%s", "lines in file: " );
	printf("%ld\n", f_table->lines);

	size_t line_number;
	do
	{
		printf("%s", "enter line number: ");
		scanf("%ld", &line_number);
		if(line_number < 0)
			{printf("%s\n", "wrong line number");}
		else if(line_number > 0)
		{
			if (line_number > f_table->lines) 
				{printf("%s\n", "wrong line number");} 
			else
			{
				lseek(f_table->fd, f_table->line_offset[line_number], 0); //от начала файла встали на начало нужной строки
				if(read(f_table->fd, buffer, f_table->line_len[line_number]) > 0)
				{
					write(1, buffer, f_table->line_len[line_number]); //пишем в терминал
				}
				else printf("%s\n", "can't read line");
			}
		}
	}
	while(line_number > 0);

	close(f_table->fd);
	free(f_table);
	return 0;
}