//extern char **environ

/*The  variable  environ points to an array of pointers to strings called
 the "environment".  The last pointer in this array has the value  NULL.*/

/*This  array  of strings is made available to the process by
the exec(3) call that started the process.  When  a  child  process  is
 created via fork(2), it inherits a copy of its parent's environment.*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int execvpe(char *file, char *nargv[], char *nenvp[])
{
    extern char **environ;
    environ = nenvp;
    execvp(file, nargv);
  	perror("execvpe");
  	return(-1);
}

int main(int argc, char* argv[])
{	
    static char *nargv[ ] = {"./exectest", "hello", "world", (char *) 0 };
    static char *nenv[ ] = { "VAR1=1111", "VAR2=2222", (char *) 0 };
    execvpe(nargv[0], nargv, nenv);
    perror(nargv[0]);
    exit(1);
}
 


