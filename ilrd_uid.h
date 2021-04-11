/**********************************************************************************************
 * 																				  			  *
 *					Exercise: UID - TEST												      *
 * 																							  *
 * 								Developer: Rafael											  *
 *																							  *
 * 								Reviewer: itay												  *
 *                                                                                            *				         
 **********************************************************************************************/
 
 /*****************************HEADERS *****************************************/
#ifndef __ILRD_UID_H__
#define __ILRD_UID_H__

#include <stddef.h>      /*    size_t            */
#include <sys/types.h>    /*    pid_t, time_t    */

 /********************STRUCTS + TYPEDEF *****************************************/
typedef struct ilrd_uid
{
    size_t counter;
    time_t time;
    pid_t pid;
} ilrd_uid_t;

/*
* Description:
* Creates a new UID 
* for it.
* If ERR SEND 
*
*
* @return:
* Returns a struct with the UID
* 
* Time Complexity O(1)
*/

ilrd_uid_t UIDCreate();

int UIDIsSame(ilrd_uid_t first, ilrd_uid_t second);

ilrd_uid_t UIDGetBadUID();

#endif /* __ILRD_UID_H__ */
