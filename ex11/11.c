//extern char **environ

/*The  variable  environ points to an array of pointers to strings called
 the "environment".  The last pointer in this array has the value  NULL.*/

/*This  array  of strings is made available to the process by
the exec(3) call that started the process.  When  a  child  process  is
 created via fork(2), it inherits a copy of its parent's environment.*/

#include <unistd.h>
#include <stdlib.h>

int execvpe(char *file, char *argv[], char *envp[]);

//#if DEBUG
#include <stdio.h>

int main()
{
    static char *argv[ ] = { "./exectest", "hello", "world", (char *) 0 };
    static char *nenv[ ] = { "RUN=yes", "FILE=data", (char *) 0 };
    execvpe(argv[0], argv, nenv);
    perror(argv[0]);
    exit(1);
}
 
//#endif


int execvpe(char *file, char *argv[], char *envp[])
{
    extern char **environ;
    char* path = getenv("PATH");
    environ = envp;
    putenv(path);
    execvp(file, argv);
    return(-1);
}