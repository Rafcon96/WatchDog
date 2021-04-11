/********************************************************************************
 *																				*
 *							Exercise: Task (Scheduler)							*
 *																				*
 *							Developer: Rafael									*
 *																				*
 * 							Reviewer: Kobi										*
 *																				*
 *							Special comments: none								*
 *																				*
 ********************************************************************************/

#ifndef __TASK_H__
#define __TASK_H__

/************************** HEADERS *********************************************/

#include <stddef.h>  	/*	size_t		*/

#include "ilrd_uid.h"	/*	ilrd_uid_t	*/

/************************** TYPE DEFINITIONS ************************************/

#ifndef TASK_FUNC
#define TASK_FUNC
typedef int (*task_func_t)(void *param);
#endif /* TASK_FUNC */


#ifndef TASK_T
#define TASK_T
typedef struct task task_t;
#endif /* TASK_T */

/************************** FUNCTION DECLARATIONS *******************************/

/* DESCRIPTION:
* Creates a new task.
*
* @param:
* task: 		Function pointer to task_func_t.
* interval:		The interval to execute the task in seconds.
* param:		Void pointer to param to be used by the function.
*
* @return:
* Returns the newly created task, or NULL if fails to create.
*/
task_t *TaskCreate(task_func_t task_func, size_t interval, void *param);

/* DESCRIPTION:
* Destroys task.
*
* @param:
* task: 	Pointer to task to be destroyed.
*/
void TaskDestroy(task_t *task);

/* DESCRIPTION:
* Set next next_run of the task.
*
* @param:
* task: 	Pointer to task to set next_time.
*/
task_t *TaskSetNextTime(task_t *task);

/* DESCRIPTION:
* Executes the function of the task.
*
* @param:
* task: 	Pointer to task to execute.
* 
* @return:
* Returns the int returned from the task function.
*/
int TaskExecute(task_t *task);

/* DESCRIPTION:
* Returns the interval of task.
*
* @param:
* task: 	Pointer to task.
* 
* @return:
* Returns the interval of task.
*/
time_t TaskGetNextRun(task_t *task);

/* DESCRIPTION:
* Returns the uid of task.
*
* @param:
* task: 	Pointer to task.
* 
* @return:
* Returns the uid of task.
*/
ilrd_uid_t TaskGetId(task_t * task);

/* DESCRIPTION:
* Returns the next_run of task.
*
* @param:
* task: 	Pointer to task.
* 
* @return:
* Returns the next_run of task.
*/
time_t TaskGetTime(task_t *task);

#endif /* __TASK_H__ */
