#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	char ch;
	printf("%s\n", "print a char:");

	int fd;
	struct termios tty; 
	struct termios savtty;

	/*Терминальный специальный файл открывается для чтения, 
	и его текущий режим запи­сывается в структуру termios. 
	Библиотечная функция isatty(3F) проверяет, связан ли файловый дескриптор 1 с терминалом. */

	if((fd = open("/dev/tty", O_RDONLY)) == -1)
	{
		perror("can't open terminal");
		exit(-1);
	}

	tcgetattr(fd, &tty);
	if (isatty(fileno(stdout)) == 0)
	{
		fprintf(stderr,"stdout not terminal\n");	
		exit(-1);
	}

	savtty = tty; 
	//tty.c_lflag &= ~(ISIG | ICANON | ECHO);
	tty.c_lflag &= ~(ISIG | ICANON);
	/*Терминальный интерфейс переводится в режим 
	неканонического ввода и без об­работки специальных символов. */

	tty.c_cc[VMIN] = 1;     /* MIN */

	/*Изменение происходит после того, 
	как весь вывод  в  fildes  был  передан,  а  непрочитанный  ввод сброшен. */
	
	if(tcsetattr(fd, TCSAFLUSH, &tty) == -1)
		perror("set attr");

	read(fd, &ch, 1);
	printf("\n%s\n", "thank you! have a nice day!");

	if(tcsetattr(fd, TCSAFLUSH, &savtty) == -1)
		perror("set attr back");

	exit(0);

}