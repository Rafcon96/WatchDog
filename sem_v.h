/*******************************************************************************
 *																			   *
 *							Exercise: Semaphore								   *
 *																			   *
 *							Developer: Omry									   *
 *																			   *
 * 							Reviewer: ?										   *
 *																			   *
 *							Special comments: none							   *
 *																			   *
 ******************************************************************************/

#ifndef __SEM_V_H__
#define __SEM_V_H__

/************************** FUNCTION DECLARATIONS *****************************/

/* DESCRIPTION:
* Creates/Opens a semaphore identified by str.
* If this created the semaphore, initializes it with value.
* the string is usedt open / creat a file in /temp, with the same
* name. This file IPC key identifaier is then used to create the semaphore.
* Thread safe.
*
* @param:
* str 			Character pointer to identifier string.
* value 		Initial value for the semaphore.
*
* @return:
* Returns the semaphore id, or -1 if failed.
*/
int SemVCreate(char const *str, unsigned int value);

/* DESCRIPTION:
* Destroys a semaphore identified by semid.
* Thread safe.
* Destroying a semaphore makes it unusable in all other threads/processes.
* Attempting to double-destroy a semaphore will fail.
*
* @param:
* semid 		Semaphore id.
*
* @return:
* Returns 0 on success, or -1 if destruction failed. Sets errno.
*/
int SemVDestroy(int semid);

/* DESCRIPTION:
* Posts to the semaphore identified by semid.
* If undo is a non-zero value, the operation will automatically be undone upon process termination.
* Thread safe.
*
* @param:
* semid 		Semaphore id.
* undo 			Flag whether to undo.
*
* @return:
* Returns 0 on success, or -1 if post failed. Sets errno.
*/
int SemVPost(int semid, int undo);

/* DESCRIPTION:
* Waits on the semaphore identified by semid.
* If undo is a non-zero value, the operation will automatically be undone upon process termination.
* Thread safe.
*
* @param:
* semid 		Semaphore id.
* undo 			Flag whether to undo.
*
* @return:
* Returns 0 on success, or -1 if wait failed. Sets errno.
*/
int SemVWait(int semid, int undo);

/* DESCRIPTION:
* Returns the value of the semaphore.
* Thread safe.
* If you wish to shoot yourself in the foot by using this to make decisions, go ahead. I do not endorse this behavior. Shooting yourself in the foot is ill advised by at least 6 out of every 5 doctors.
* Warning: If your doctor hates you, or wishes to get you out of the army, he may not advise against it.
*
* @param:
* semid 		Semaphore id.
*
* @return:
* Returns the value of the semaphore, or -1 if failed. Sets errno.
*/
int SemVGetValue(int semid);

#endif /* __SEM_V_H__ */