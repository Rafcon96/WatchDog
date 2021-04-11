

/************************ PREPROCESSOR ******************************/
#ifndef __Wd_H__
#define __WD_H__

/************************ FUNCTION DECLARATIONS    ******************/

/* DESCRIPTION:
* Creates a new Watchdog app, which in turn, creates a new watchdog.
* Scheduler creation may fail and return -1.
* sigaction may fail and return -1.
* Semaphore initialization may fail and return -1
* 
* The program timeout is set to 30 seconds, meaning that the program
* will exit after said time of continuous user_app runtime.
*
* The program checks every 5 seconds for whether any signal has been received
* from the watchdog and vice versa. In case no signal has been received during
* said period, an attempt to shut down the unresponsive part will occur, followed
* by an attempt to revive the unresponsive part.
*
* In case a revive is unsuccessful, the program will quit, shutting down and
* freeing any allocated space and open threads.
*
* @param:
* is_app_wd 	user provided flag, must be set to 1 by the user.
* argc          user's program argument count.
* argv          user's program argument values.
*
* @return:
* Returns 0 on success and -1 if an error has been encountered.
*/
int StartWD(int caller, char *argv[]);

/* DESCRIPTION:
* Stops the Watchdog app, which in turn, stops the watchdog watchdog.
* Removes any threads and frees any memory allocated for the watchdog.
*
* @return:
* Returns 0 on success and a non-zero if an error has been encountered
* during the watchdog shutdown.
*/
int StopWD();


#endif /* __WD_H__ */
