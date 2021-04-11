/********************************************************************************
 *																				*
 *							Exercise: Priority queue							*
 *																				*
 *							Developer: Which Team?								*
 *																				*
 * 							Reviewer: ?											*
 *																				*
 *							Special comments: none								*
 *																				*
 ********************************************************************************/

#ifndef __PQUEUE_H__
#define __PQUEUE_H__

/************************** HEADERS *********************************************/

#include <stddef.h>  	/*	size_t		*/
		
#include "sorted_l.h"



/************************** TYPE DEFINITIONS ************************************/

typedef struct pqueue pqueue_t;

#ifndef COMPARE_FUNC
#define COMPARE_FUNC

typedef int (*compare_func_t)(const void *first, const void *second);
/* Function returns 1, 0, or -1, if first is "has higher importance than" "has same importance as" or "has lower importance than" second */

#endif /* COMPARE_FUNC */

#ifndef IS_MATCH
#define IS_MATCH

typedef int (*ismatch_func_t)(const void *first, const void *second);
/* Function returns 1 if first is equal to second, and 0 otherwise. */

#endif /* IS_MATCH */

/************************** FUNCTION DECLARATIONS *******************************/

/* DESCRIPTION:
* Creates a new priority queue, with order function comparison.
* O(1) complexity.
*
* @param:
* comparison 	Function pointer to comparison function.
*
* @return:
* Returns the newly created priority queue.
*/
pqueue_t *PQCreate(compare_func_t comparison);

/* DESCRIPTION:
* Destroys priority queue.
* O(n) complexity.
*
* @param:
* pqueue 		Pointer to pqueue to be destroyed.
*/
void PQDestroy(pqueue_t *pqueue);

/* DESCRIPTION:
* Creates a new element from data, with priority determined by pqueue.
* Inserts this new element into pqueue.
* For elements with the same priority, this behaves as a normal queue.
* O(n) complexity.
*
* @param:
* pqueue 		Pointer to pqueue to be added to.
* data 			Pointer to data to be inserted to pqueue.
*
* @return:
* Returns 0 on success, and -1 if failed to allocate a new member into the queue.
*/
int PQEnqueue(pqueue_t *pqueue, void *data);

/* DESCRIPTION:
* Removes the highest priority element from pqueue.
* Attempting to dequeue from an empty queue will result in undefined behavior.
* O(1) complexity.
*
* @param:
* pqueue 		Pointer to pqueue to be removed from.
*
* @return:
* The popped element, or NULL if pqueue is empty.
*/
void *PQDequeue(pqueue_t *pqueue);

/* DESCRIPTION:
* Peeks at the front element of pqueue.
* O(1) complexity.
*
* @param:
* pqueue		A pointer to the pqueue to be peeked at.
*
* @return:
* The peeked element, or NULL if pqueue is empty.
*/
void *PQPeek(const pqueue_t *pqueue);

/* DESCRIPTION:
* Returns the current size of pqueue.
* O(n) complexity.
*
* @param:
* pqueue		A pointer to the pqueue.
*
* @return:
* The current size of the pqueue.
*/
size_t PQSize(const pqueue_t *pqueue);

/* DESCRIPTION:
* Checks if the pqueue is empty.
* O(1) complexity.
*
* @param:
* pqueue		A pointer to the pqueue.
*
* @return:
* True (1) if the queue is empty. 0 otherwise.
*/
int PQIsEmpty(const pqueue_t *pqueue);

/* DESCRIPTION:
* Searches for an element in the queue with value data, using match function.
* If found, it is erased.
* O(n) complexity.
*
* @param:
* pqueue		A pointer to the pqueue.
* data 			Pointer to data to be erased from pqueue.
* match 		Function pointer to search function.
*
* @return:
* Returns erased data, or NULL if none was found.
*/
void *PQErase(pqueue_t *pqueue, void *param, ismatch_func_t match);

/* DESCRIPTION:
* Removes all elements from the queue.
* O(n) complexity.
*
* @param:
* pqueue		A pointer to the pqueue.
*/
void PQClear(pqueue_t *pqueue);

#endif /* __PQUEUE_H__ */
