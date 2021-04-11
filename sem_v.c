/*******************************************************************************
 *																			   *
 *							Exercise: System-V Semaphore Wraper 			   *
 *																			   *
 *							Developer: Hannah Gajst							   *
 *																			   *
 * 							Reviewer: ?										   *
 *																			   *
 *							Special comments: none							   *
 *																			   *
 ******************************************************************************/

/************************** HEADERS *******************************************/

#include <stdio.h>	/*	fopen()						*/
#include <stdlib.h> /*	malloc(), free()			*/
#include <string.h> /*	strlen(), strcat(), strcpy()*/
#include <assert.h> /*	assert()		 			*/
#include <errno.h>	/*	errno						*/

/* For System V semaphores */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#include "sem_v.h" /*	Headers for this file		*/

/************************** TYPE DEFINITIONS **********************************/

/* We must define this... */
union semun
{
	int val;			   /* Value for SETVAL */
	struct semid_ds *buf;  /* Buffer for IPC_STAT, IPC_SET */
	unsigned short *array; /* Array for GETALL, SETALL */
	struct seminfo *__buf; /* Buffer for IPC_INFO (Linux-specific) */
};

/************************** FUNCTION DEFINITION *******************************/

int SemVCreate(char const *str, unsigned int value)
{
	int permissions = 0660;
	int proj_id = 255;
	int semflg = permissions | IPC_CREAT | IPC_EXCL;
	union semun semctl_union = {0};
	FILE *fp = NULL;
	key_t key;
	int semid = 0;

	/* Using the string, create a temporary file. */
	/* Plus 1 for NULL terminator, plus 5 for /tmp/ */
	char *file_name = malloc(strlen(str) + 1 + 5);
	if (!file_name)
	{
		return -1;
	}
	strcpy(file_name, "/tmp/");
	strcat(file_name, str);
	fp = fopen(file_name, "w");
	if (!fp)
	{
		free(file_name);
		return -1;
	}
	/* fclose can only fail if fp if invalid, which was checked earlier when fopen returned. */
	fclose(fp);

	/* Use the (possibly) newly created file to generate a key. */
	key = ftok(file_name, proj_id);
	/* Free file name */
	free(file_name);
	/* Get a semaphore using the key */
	semid = semget(key, 1, semflg);

	/* Check if creation failed. */
	if (-1 == semid)
	{
		struct semid_ds data = {0};
		semctl_union.buf = &data;

		/* Check if the failure was not because it already exists. */
		if (EEXIST != errno)
		{
			return -1;
		}

		/* Otherwise, it failed because it exists, get it. */
		semflg = permissions | IPC_CREAT;
		semid = semget(key, 1, semflg);

		/* Check if we couldn't get the semid for some reason. Now this can't be EEXIST because we don't have IPC_EXCL in the flag. */
		if (-1 == semid)
		{
			return -1;
		}

		/* Check to see if it was initialized. This may be currently getting initialized by another thread, and so this must be a while loop. */

		/* Note: If whoever created the semaphore does not perform an operation on it, this will never update. */
		while (0 == data.sem_otime)
		{
			semctl(semid, 0, IPC_STAT, semctl_union);
		}
	}
	/* Initialize it. */
	else
	{
		unsigned short initial_value = value + 1;
		semctl_union.array = &initial_value;

		semctl(semid, 0, SETALL, semctl_union);
		/* Set the value to 1 more, then wait, so sem_otime is not zero. */
		SemVWait(semid, 0);
	}

	return semid;
}

int SemVDestroy(int semid)
{
	return semctl(semid, 0, IPC_RMID);
}

int SemVPost(int semid, int undo)
{
	struct sembuf sops = {0};
	sops.sem_num = 0;
	sops.sem_op = 1;
	sops.sem_flg = undo ? SEM_UNDO : 0;

	return semop(semid, &sops, 1);
}

int SemVWait(int semid, int undo)
{
	struct sembuf sops = {0};
	sops.sem_num = 0;
	sops.sem_op = -1;
	sops.sem_flg = undo ? SEM_UNDO : 0;

	return semop(semid, &sops, 1);
}

int SemVGetValue(int semid)
{
	return semctl(semid, 0, GETVAL);
}
