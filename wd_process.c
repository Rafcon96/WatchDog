/*/////////////////////////////////////////////////////////////////////*/

#include <signal.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>

/*---------------------------- HEADER FILES -------------------------------*/

#include "watchdog.h"




/*-------------------------- AUXILARY FUNCTIONS ---------------------------*/

int main(int argc, char *argv[])
{	
	fprintf(stderr, "in process wd\n");
	StartWD(1, argv);
	
	return 0;
}




