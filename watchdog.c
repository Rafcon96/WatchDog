	
#define _GNU_SOURCE 		
#include <stdio.h>
#include <signal.h>
#include <assert.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#include "watchdog.h"
#include "sem_v.h"
#include "scheduler.h"
#include "utilities.h"

/************************** GLOBAL VARIABLES & TYPES *************************/

/* semaphores */
static int thread_set;
static int process_set;

static pid_t remote_pid;
static scheduler_t *scheduler;
static char **g_argv;
static unsigned int counter;
static pthread_t wd_thread;
static ilrd_uid_t task1 = {0};
static ilrd_uid_t task2 = {0};
static ilrd_uid_t task3 = {0};
static ilrd_uid_t task4 = {0};

enum CALLER {
    APP,    /* app thread */
    WD      /* wd process */
};


#define UNDO (1)
#define FAILURE (-1)
#define SUCCESS (0)

/************************* FUNCTION DECLARATIONS *****************************/

static void SigHandler1(int sig);
static void SigHandler2(int sig);

static int InitSigHandlersImp(void);
static int InitSemsImp(void); 
static int InitSchedulerImp(int caller);

static pid_t CreateProcessImp(int caller);

static void SemDestroyImp();
static void DestroySchdAndSemsImp();

static void *RunWDthreadImp(void *param);
static void RunWDProcessImp();
static int AppTask1(void *param);
static int AppTask2(void *param);
static int WDTask1(void *param);
static int WDTask2(void *param);
static int WDTask3(void *param);
static int WDTask4(void *param);

/**************************** FUNCTION DEFINITIONS ***************************/			

/********************************* START WD **********************************/

int StartWD(int caller, char *argv[])
{
    g_argv = argv;
    printf("starting process %d 0 app 1 wd\n", caller);
	
    if (SUCCESS != InitSemsImp() || SUCCESS != InitSigHandlersImp())
    {
        SemDestroyImp();
        ERR_PRINT();
        return FAILURE;
    }
   
    if (SUCCESS != InitSchedulerImp(caller))
    {
        SemDestroyImp(); 
        ERR_PRINT();
        return FAILURE;
    }

    if (APP == caller)
    { 
		if (NULL == getenv("WD") || getppid() != atoi(getenv("WD")))
		{
			fprintf(stderr,"***  no wd alive \n");
			remote_pid = CreateProcessImp(caller);
		}
		else
		{
			remote_pid =  getppid() ;
			fprintf(stderr,"*** wd alive at set up\n");
		}

        if (FAILURE == remote_pid)
        {
            DestroySchdAndSemsImp();
            ERR_PRINT();
            return FAILURE;
        }
           
        (getppid() != remote_pid) ? SemVWait(process_set, UNDO) : 0;

        if (SUCCESS != pthread_create(&wd_thread, NULL, &RunWDthreadImp, NULL))
        {
            DestroySchdAndSemsImp();
            ERR_PRINT();
            return FAILURE;
        }

        SemVPost(thread_set, UNDO);
    }
	/* the caller is the WD */
    else
    {
        remote_pid = getppid();
        SemVPost(process_set, UNDO);
        (getppid() == remote_pid) ? SemVWait(thread_set, UNDO) : 0;
        RunWDProcessImp();
        SchedulerDestroy(scheduler);
    }

    return SUCCESS;
}

/*********************************** STOP WD *********************************/

int StopWD()
{
    
    /* consider stop, remove and run */
    SchedulerRemoveTask(scheduler, task2);

    if (FAILURE == kill(remote_pid, SIGUSR2))
    {
        kill(remote_pid, SIGKILL); 
    }
   
    SchedulerStop(scheduler);   
    pthread_join(wd_thread, NULL);

    SemDestroyImp();
    

    return SUCCESS;
}

/****************************** INIT FUNCTIONS *******************************/

static int InitSigHandlersImp()
{
    struct sigaction act1 = {0};
    struct sigaction act2 = {0};

    act1.sa_handler = SigHandler1;
    act2.sa_handler = SigHandler2;

    if (sigaction(SIGUSR1, &act1, NULL) || sigaction(SIGUSR2, &act2, NULL))
    {
        return FAILURE;
    }

    return SUCCESS;
}

/****************************************************************************/

static int InitSemsImp() 
{
	if (FAILURE == (process_set = SemVCreate("sched_set", 0))     ||
        FAILURE == (thread_set = SemVCreate("thread_set", 0)))       
    { 
        ERR_PRINT();
        return FAILURE; 
    }    
    
    return SUCCESS;    
}

/****************************************************************************/

static int InitSchedulerImp(int caller)
{
    scheduler = SchedulerCreate();
 
    if( NULL == scheduler)
    {
        ERR_PRINT();
        return FAILURE;
    }

    if (caller == APP)
    {
        task1 = SchedulerAddTask(scheduler, AppTask1, 1, NULL);
        task2 = SchedulerAddTask(scheduler, AppTask2, 5, NULL);
    }

    else
    {
        task1 = SchedulerAddTask(scheduler, WDTask1, 1, NULL);
        task2 = SchedulerAddTask(scheduler, WDTask2, 5, NULL);
        task3 = SchedulerAddTask(scheduler, WDTask3, 12, NULL);
        task4 = SchedulerAddTask(scheduler, WDTask4, 15, NULL);
    }

    if (UIDIsSame(UIDGetBadUID(), task1) || UIDIsSame(UIDGetBadUID(), task2) )
    {
        SchedulerDestroy(scheduler);
        ERR_PRINT();
        return FAILURE;
    }
    
    return SUCCESS;
}

/****************************************************************************/

static pid_t CreateProcessImp(int caller)
{
    pid_t pid = fork();
  

    if (0 == pid)
    {
        if (APP == caller)
        {
		    char num[5] = {0};
		    pid = getpid();
		    
		    sprintf(num, "%d",pid);

		    setenv("WD", num, 1);
            execv("wd_p", g_argv);
            
            return FAILURE;
        }

        else
        {
            execv(g_argv[0], g_argv);
            return FAILURE;
        }
    }

    if (-1 == pid)
    {
        ERR_PRINT();
        return FAILURE;
    }

    return pid;
}

/***************************** DESTROY FUNCTIONS *****************************/

static void SemDestroyImp()
{
    SemVDestroy(process_set);
    SemVDestroy(thread_set);
}

/****************************************************************************/

static void DestroySchdAndSemsImp()
{
    SchedulerStop(scheduler);
    SchedulerDestroy(scheduler);
    scheduler = NULL;
    SemDestroyImp();
}

/****************************** TASKS FUNCTIONS ******************************/

static int AppTask1(void *param)
{
    (void)param;
    kill(remote_pid, SIGUSR1);
    return SUCCESS;
}

/****************************************************************************/

static int AppTask2(void *param)
{
    (void)param;
 
	if (0 == counter)
    {
        if (FAILURE == kill(remote_pid, SIGUSR2))
        {
			kill(remote_pid, SIGKILL);
        }

        remote_pid = CreateProcessImp(APP);
        
        if (-1 == remote_pid)
        {
            DestroySchdAndSemsImp();
            ERR_PRINT();
            return FAILURE;
        }

        SemVWait(process_set, UNDO);
    }

    __sync_fetch_and_and(&counter, 0);

    return SUCCESS;
}

/****************************************************************************/

static int WDTask1(void *param)
{
    (void)param;
    kill(remote_pid, SIGUSR1);

    return SUCCESS;
}

/****************************************************************************/

static int WDTask2(void *param)
{
    (void)param;
	if (0 == counter)
    {
        if (FAILURE == kill(remote_pid, SIGUSR2))
        {
			kill(remote_pid, SIGKILL);
        }

        remote_pid = CreateProcessImp(WD);
       
        if (-1 == remote_pid)
        {
            DestroySchdAndSemsImp();
            ERR_PRINT();
            return FAILURE;
        }

        SemVWait(thread_set, UNDO);
    }

    __sync_fetch_and_and(&counter, 0);  

    return SUCCESS;
}

static int WDTask3(void *param)
{
	(void)param;
    kill(remote_pid, SIGKILL);
    return SUCCESS;
}
static int WDTask4(void *param)
{
	(void)param;
	SchedulerRemoveTask(scheduler,task3);
    return SUCCESS;
}

/****************************** SIGNAL HANDLERS ******************************/

static void SigHandler1(int sig)
{
    (void)sig;
	__sync_fetch_and_add(&counter, 1);  
}

/****************************************************************************/

static void SigHandler2(int sig)
{
    (void)sig;
    SchedulerStop(scheduler);
}

/****************************** RUN SCHEDULERS *******************************/

static void *RunWDthreadImp(void *param)
{
    (void)param;

    SchedulerRun(scheduler);
    SchedulerDestroy(scheduler);

    return NULL;
}

/****************************************************************************/

static void RunWDProcessImp()
{
    SchedulerRun(scheduler);
}
