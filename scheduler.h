/********************************************************************************
 *																				*
 *							Exercise: Scheduler									*
 *																				*
 *							Developer: Quack Team								*
 *																				*
 * 							Reviewer: ?											*
 *																				*
 *							Special comments: none								*
 *																				*
 ********************************************************************************/

#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

/************************** HEADERS *********************************************/

/*
In scheduler.c:

struct scheduler
{
    pqueue_t *tasks;
    int stop; // flag 
};
*/



#include <stddef.h>  	/*	size_t						*/

#include "ilrd_uid.h"	/*	ilrd_uid_t					*/

/************************** TYPE DEFINITIONS ************************************/

#ifndef TASK_FUNC
#define TASK_FUNC
typedef int (*task_func_t)(void *param);
#endif /* TASK_POINTER */
/* Function returns 0 for re-schedule, and anything else to not be re-scheduled. */


typedef struct scheduler scheduler_t;

#ifndef TASK_T
#define TASK_T
typedef struct task task_t;
#endif /* TASK_T */
/************************** FUNCTION DECLARATIONS *******************************/

/* DESCRIPTION:
* Creates a new scheduler.
* O(1) complexity.
*
* @return:
* Returns the newly created scheduler, or NULL if failed to create.
*/
scheduler_t *SchedulerCreate(void);

/* DESCRIPTION:
* Destroys scheduler.
* O(n) complexity.
*
* @param:
* scheduler 	Pointer to scheduler to be destroyed.
*/
void SchedulerDestroy(scheduler_t *scheduler);

/* DESCRIPTION:
* Starts running the scheduler scheduler.
* Keep running until scheduler is empty or 'stop' is invoked.
* O(1) complexity.
*
* @param:
* scheduler 	Pointer to scheduler to be destroyed.
*
* @return:
* Returns 0 if scheduler is empty. Return 1 is 'stop' is invoked.
*/
int SchedulerRun(scheduler_t *scheduler);

/* DESCRIPTION:
* Stops running the scheduler scheduler.
* O(1) complexity.
*
* @param:
* scheduler 	Pointer to scheduler to be destroyed.
*/
void SchedulerStop(scheduler_t *scheduler);

/* on fail returns bad uid */
/* Enqueue may fail */
/* interval counts seconds so size_t is enough */
ilrd_uid_t SchedulerAddTask(scheduler_t *scheduler, task_func_t task_func, size_t interval, void *param);


/* DESCRIPTION:
* Removes task from scheduler.
* O(n) complexity.
*
* @param:
* scheduler 	Pointer to scheduler to be removed from.
* task 			Pointer to identifier of task to be removed.
*/
/* user may ask to remove non existing param */
/* Return 0 if task was found, otherwise return 1 */
int SchedulerRemoveTask(scheduler_t *scheduler, ilrd_uid_t task);

/* DESCRIPTION:
* Returns the current size of scheduler.
* O(n) complexity.
*
* @param:
* scheduler 	Pointer to scheduler.
*
* @return:
* The current size of the scheduler.
*/
size_t SchedulerSize(const scheduler_t *scheduler);

/* DESCRIPTION:
* Checks if the scheduler is empty.
* O(1) complexity.
*
* @param:
* scheduler 	Pointer to scheduler.
*
* @return:
* True (1) if the scheduler is empty. 0 otherwise.
*/
int SchedulerIsEmpty(const scheduler_t *scheduler);

/* DESCRIPTION:
* Removes all elements from the scheduler.
* O(n) complexity.
*
* @param:
* scheduler 	Pointer to scheduler to be cleared.
*/
void SchedulerClear(scheduler_t *scheduler);

#endif /* __SCHEDULER_H__ */
