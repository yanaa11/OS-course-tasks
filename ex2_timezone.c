#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <string.h>

extern char *tzname[];

const char* californiaTZ= "America/Los_Angeles";


int main()
{
    char oldTZ[80];
    char* currentTZ = getenv("TZ");
    if (currentTZ) 
        strncpy(oldTZ, currentTZ, 79); 

    if (setenv("TZ", californiaTZ, 1) == -1)
    {
        printf("%d %s", errno, strerror(errno));
        exit(-1);
    }
       

    time_t seconds = time(NULL);
    struct tm* timeStruct = localtime(&seconds); //localtime откуда временную зону берет???????????????????
    if (!timeStruct)
    {
        printf("%d %s", errno, strerror(errno));
        exit(-1);
    }

    printf("%d/%d/%02d %d:%02d %s\n",
         timeStruct->tm_mon + 1, timeStruct->tm_mday,
         timeStruct->tm_year, timeStruct->tm_hour,
         timeStruct->tm_min, tzname[timeStruct->tm_isdst]);

    if (setenv("TZ", oldTZ, 1) == -1)
    {
        printf("%d %s", errno, strerror(errno));
        exit(-1);
    }
     exit(0);
}

