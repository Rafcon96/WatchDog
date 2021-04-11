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

/************************** HEADERS *********************************************/

#include "task.h"	/*	ilrd_uid_t	*/
#include <stdlib.h>
#include <time.h>
#include <assert.h>

/************************** TYPE DEFINITIONS ************************************/

struct task
{
	ilrd_uid_t id;
	task_func_t execute;
	void *param;
	size_t interval;
	time_t next_run;
};

/************************** FUNCTION DECLARATIONS *******************************/

task_t *TaskCreate(task_func_t task_func, size_t interval, void *param)
{
	task_t *new_task = malloc(sizeof(task_t));
	
	assert(NULL != task_func);
	
	
	if (NULL == new_task)
	{
		return NULL;
	}
	
	new_task->id = UIDCreate();
	new_task->execute = task_func ;
	new_task->param = param;
	new_task->interval = interval;
	new_task->next_run = interval + time(NULL);
	
	return new_task;
}

void TaskDestroy(task_t *task)
{
	assert(NULL != task);
	free(task);
}

task_t *TaskSetNextTime(task_t *task)
{
	assert(NULL != task);
	
	task->next_run = time(NULL) + task->interval;
	
	return task;
}

time_t TaskGetNextRun(task_t *task)
{
	assert(NULL != task);
	
	return task->next_run;
}

ilrd_uid_t TaskGetId(task_t * task)
{
	return task->id;
}

int TaskExecute(task_t *task)
{
    assert(NULL != task);
    
    return task->execute(task->param);
}



