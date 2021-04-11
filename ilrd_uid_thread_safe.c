/**********************************************************************************************
 * 																				  			  *
 *					Exercise: UID - SRC 												      *
 * 																							  *
 * 								Developer: Rafael											  *
 *																							  *
 * 								Reviewer: itay												  *
 *                                                                                            *				         
 **********************************************************************************************/
 /*****************************HEADERS *****************************************/
 
#include <stddef.h>   /*    size_t           */
#include <unistd.h>   /*    pid_t            */
#include <time.h>	  /*     time_t          */

#include "ilrd_uid.h" /*    pid_t, time_t    */


ilrd_uid_t UIDCreate()
{
	static size_t counter = 0;
	ilrd_uid_t uid = {0};
	uid.counter = __sync_fetch_and_add(&counter, 1); 
	uid.time = (time_t)time(NULL);
	uid.pid = getpid();
	
	return uid;
}

int UIDIsSame(ilrd_uid_t first, ilrd_uid_t second)
{
	int result = 0;
	
	if (first.counter == second.counter && first.time == second.time && first.pid == second.pid)
	{
		result = 1;
	}
	
	return result;
}

ilrd_uid_t UIDGetBadUID()
{
	ilrd_uid_t uid = {0};
	uid.counter = 0;
	uid.time = (time_t)0;
	uid.pid = (pid_t)0;
	return uid;
}


