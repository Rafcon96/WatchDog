/*/////////////////////////////////////////////////////////////////////*/

#include <stdio.h>   /* printf() fprintf()  */
#include <assert.h>  /* assert()          	*/
#include <unistd.h>
#include <time.h>

/*---------------------------- HEADER FILES -------------------------------*/

#include "watchdog.h"

/*-------------------------------- MACROS ---------------------------------*/

#define RUN_TIME (30)

/*-------------------------------------------------------------------------*/
/*                              MAIN PROGRAM                               */
/*-------------------------------------------------------------------------*/

int main(int argc, char *argv[])
{
	double start = time(NULL);
	int status = StartWD(0 ,argv);
	size_t counter = 0;
	
	if (status)
	{
		StopWD();
	}

   	while(time(NULL) - start < RUN_TIME)
	{
		(void)counter;
		
	}	

	fprintf(stderr, "Application: stop running..\n");
	
	StopWD();

	return 0;
}
