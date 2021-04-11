/********************************************************************************
 *																				*
 *							Exercise: Scheduler									*
 *																				*
 *							Developer: Rafael									*
 *																				*
 * 							Reviewer: kobi										*
 *																				*
 ********************************************************************************/

/************************** HEADERS *********************************************/

#include <stdlib.h>   /* malloc(), free()   */
#include <time.h>	  /* time(), difftime() */
#include <assert.h>   /* assert()           */

#include <unistd.h>   /* sleep()            */

#include "task.h"
#include "ilrd_uid.h"
#include "pqueue.h"
#include "scheduler.h"
#include "utilities.h"

/****************************MACRO ***********************************************/

#ifndef COMP_FUNC
#define COMP_FUNC
#define COMPARE(x, y) (((x) > (y)) - ((x) < (y)))
#endif /* COMP_FUNC */ 
/* 1 if x > y, -1 if y > x, 0 if y = x */

/************************** STRUCT DEFINITIONS **********************************/

struct scheduler
{
    pqueue_t *tasks_pq;
    int is_stop; 
    task_t *curr_task;
};

/*********************************** ENUM ************************************/

enum STATUS{RESCHEDULE, NOT_RESCHEDULE};

/************************** FUNCTION DEFINITIONS *******************************/
static int CompareIdIMP(const void *first, const void *second);

static int IsIdMatchIMP(const void *first, const void *second);

/************************** FUNCTION DECLARATIONS *******************************/
scheduler_t *SchedulerCreate(void)
{
	scheduler_t *scheduler = malloc(sizeof(scheduler_t));
	
	if (NULL == scheduler)
	{
		ERR_PRINT();
		
		return NULL;
	}
	
	if (NULL == (scheduler->tasks_pq = PQCreate(CompareIdIMP)))
	{
		free(scheduler);
		ERR_PRINT();
		
		return NULL;
	}

	scheduler->is_stop = 0;
	scheduler->curr_task = NULL;
	
	return scheduler;
}

void SchedulerDestroy(scheduler_t *scheduler)
{
	assert(NULL != scheduler);

	SchedulerClear(scheduler);

	PQDestroy(scheduler->tasks_pq);
	
	scheduler->tasks_pq = NULL;
	scheduler->curr_task = NULL;
	
	free(scheduler);
	scheduler =NULL;
}

int SchedulerRun(scheduler_t *scheduler)
{
	int status = RESCHEDULE;
	int next_run = 0;
		
	assert(NULL != scheduler);
	
	/* run till list is empty or after changing stop flag to 1 */
	while (!scheduler->is_stop && !SchedulerIsEmpty(scheduler))
	{
		/* check the first element next run to know who mutch to sleep */
		next_run = difftime(TaskGetNextRun(PQPeek(scheduler->tasks_pq)), time(NULL));
		
		if (next_run > 0)
		{
			while(next_run)
			{
				next_run = sleep(next_run);
			}
			
		}

		if (0 <= difftime(TaskGetNextRun(PQPeek(scheduler->tasks_pq)), time(NULL)))
		{
			/* update curr task that run & exacute it */
			scheduler->curr_task = PQDequeue(scheduler->tasks_pq);
			status = TaskExecute(scheduler->curr_task);
						
			if (NULL != scheduler->curr_task)
			{
				if (RESCHEDULE == status)
				{	/* update next run */
					TaskSetNextTime(scheduler->curr_task);
					PQEnqueue(scheduler->tasks_pq, scheduler->curr_task);
				}
				else
				{
					TaskDestroy(scheduler->curr_task);
				}
				
				scheduler->curr_task = NULL;
			}
		}
	}
	
	if (1 == scheduler->is_stop)
	{
		scheduler->is_stop = 0;
		return 1;
	}
	
	return 0;
}

void SchedulerStop(scheduler_t *scheduler)
{
	assert(NULL != scheduler);

	scheduler->is_stop = 1;
}

ilrd_uid_t SchedulerAddTask(scheduler_t *scheduler, task_func_t task_func, size_t interval, void *param)
{
	task_t *new_task = NULL;
	
	assert(NULL != scheduler);
	assert(NULL != task_func);
	
	new_task = TaskCreate(task_func, interval, param);
	
	if (PQEnqueue(scheduler->tasks_pq, new_task))
	{
		return UIDGetBadUID();
	}

	return TaskGetId(new_task);
}


int SchedulerRemoveTask(scheduler_t *scheduler, ilrd_uid_t task_id)
{
	task_t *task_remove = NULL;
	int status = 1;
	
	assert(NULL != scheduler);
	
	if (NULL != scheduler->curr_task && UIDIsSame(TaskGetId(scheduler->curr_task), task_id))	
	{
		TaskDestroy(scheduler->curr_task);
		scheduler->curr_task = NULL;
		status = 0;
	}
	else if (NULL != (task_remove = PQErase(scheduler->tasks_pq, &task_id, IsIdMatchIMP)))
	{
		TaskDestroy(task_remove);
		status = 0;
	}
	
	return status;
}

size_t SchedulerSize(const scheduler_t *scheduler)
{
	assert(NULL != scheduler);
	
	return PQSize(scheduler->tasks_pq);
}

int SchedulerIsEmpty(const scheduler_t *scheduler)
{
	assert(NULL != scheduler);
	
	return PQIsEmpty(scheduler->tasks_pq);
}

void SchedulerClear(scheduler_t *scheduler)
{
	assert(NULL != scheduler);
		
	while (!SchedulerIsEmpty(scheduler))
	{
		TaskDestroy(PQDequeue(scheduler->tasks_pq));
	}
	
	if (NULL != scheduler->curr_task)
	{
		TaskDestroy(scheduler->curr_task);
		scheduler->curr_task = NULL;
	}
}

int CompareIdIMP(const void *first, const void *second)
{
	assert(NULL != first);
	assert(NULL != second);
		
	return COMPARE(TaskGetNextRun((task_t *)first),TaskGetNextRun((task_t *)second));
}

int IsIdMatchIMP(const void *first, const void *second)
{
	task_t *task = (task_t *)first;
	ilrd_uid_t *id  = (ilrd_uid_t *)second;
	int result = 0;
	
	if (UIDIsSame(TaskGetId(task), *id))
	{
		result = 1;
	}

	return result;
}


