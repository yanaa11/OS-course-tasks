#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

main()
{
	pid_t pid, ret;
    int status;

    if ((pid = fork()) == 0)        /* child */
        execl("/bin/cat", "cat", "/etc/passwd", (char *) 0);

    printf("parent: waiting for child: %ld\n", pid);

 /* by adding a wait(2) the parent is guaranteed to finish after its child */
     
    ret = wait(&status);

    printf("parent: wait's return value: %ld,", ret);
    printf("child's status: %d\n", WEXITSTATUS(status));

    exit(0);
 }