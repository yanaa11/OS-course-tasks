#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
    FILE* f;
    int status;
    char result[100];
 
    f = popen("grep \"^$\" /home/yana/OS/emptylines.txt | wc1 -l ", "r");

    if(f == NULL)
    {
        perror("popen");
        exit(-1);
    }

    fgets(result, 100, f);

    /* pclose():  on  success,  returns  the  exit  status  of the command; if
       wait4(2) returns an error, or some  other  error  is  detected,  -1  is
       returned. */

    if((status = pclose(f)) != 0)
    {
        if(status == -1)
            perror("pclose");

        else
        {
            printf("%d\n", status);
            if(WIFEXITED(status) != 0) 
            printf("exit status: %d\n", WEXITSTATUS(status));

            if(WIFSIGNALED(status) != 0) 
            printf("signal: %d\n", WTERMSIG(status));
        }

        //exit(-1);
    }

    printf("%s", result);

    exit(0);
}