/********************************************************************************
 *																				*
 *							Exercise: Sorted List								*
 *																				*
 *							Developer: Quartz team								*
 *																				*
 * 							Reviewer: ?											*
 *																				*
 *							Special comments: none								*
 *																				*
 ********************************************************************************/

#ifndef __SORTED_L_H__
#define __SORTED_L_H__

/************************** HEADERS *********************************************/

#include <stddef.h>  	/*	size_t			*/

#include "dll.h"		/*	dll container	*/

/************************** TYPE DEFINITIONS ************************************/



typedef struct sorted_l sorted_l_t;

struct sl_iterator
{
	diterator_t iter;
	#ifndef NDEBUG
	const sorted_l_t *list;
	#endif /* NDEBUG */
};

typedef struct sl_iterator sl_iterator_t;

#ifndef COMPARE_FUNC
#define COMPARE_FUNC

typedef int (*compare_func_t)(const void *first, const void *second);
/* Function returns 1, 0, or -1, if first is "greater than" "equal to" or "lesser than" second */

typedef int (*operation_func_t)(void *data, void *param);

#endif /* COMPARE_FUNC */

#ifndef IS_MATCH
#define IS_MATCH

typedef int (*ismatch_func_t)(const void *first, const void *second);
/* Function returns 1 if first is equal to second, and 0 otherwise. */

#endif /* IS_MATCH */

/************************ FUNCTION DECLARATIONS    ******************/
/*
* Description:
* Creates a new sorted list by allocating memory
* for it.
* If compariso is NULL it will cause undefined behavior.
*
* @param:
* comparison:	a pointer to a comparison function that
* determines the sort of the list.
* the function will be of the type int compare_func_t (const void *first, const void *second)
* and will return a positive number if first is "bigger" than second,
* a negative number if first is smaller than second,
* and zero if first and second are equal.
*
* @return:
* Returns a pointer to the new created list.
* Returns NULL if fails.
* 
* Time Complexity O(1)
*/
sorted_l_t *SortedLCreate(compare_func_t comparison);

/*
* Description:
* Deletes user_list by freeing all allocated
* memory of its elements.
* If user_list is NULL it will cause undefined behavior.
*
* @param:
* user_list:	a pointer to a sorted list.
* 
* Time Complexity O(n)
*/
void SortedLDestroy(sorted_l_t *list);

/*
* Description:
* Insert data to a new node in user_list
* by allocating memory for the new node.
* The node will be inserted in an oredered
* position. 
* Changing the value referenced by data after 
* inserting it will affect the user_list order.
* 
* @param:
* user_list:	a pointer to a sorted list.
* data:			a pointer to the data we want to insert. 
*
* @return:
* Returns the iterator of the new node.
* Returns the end node of the list if fails.
*
* Time Complexity O(n)
*/
sl_iterator_t SortedLInsert(sorted_l_t *list, void *value);

/*
* Description:
* Removes where by freeing its
* allocated memory. 
* Invalidate the iterator where.
* if where is invalidate it will cause undefined behavior.
*
* @param:
* where:	an iterator to a sorted list node.
* 
* @return:
* Returns the iterator of next node after where.
* 
* Time Complexity O(1)
*/
sl_iterator_t SortedLRemove(sl_iterator_t);

/*
* Description:
* Removes the first node of user_list
* by freeing its allocated memory. 
* If user_list is NULL it will cause undefined behavior.
* If the list is empty, it will cause undefined behavior. 
*
* @param:
* user_list:	a pointer to a sorted list.
* 
* @return:
* Returns data in the first node.
* 
* Time Complexity O(1)
*/
void *SortedLPopFront(sorted_l_t *list);

/*
* Description:
* Removes the last node of user_list
* by freeing its allocated memory. 
* If user_list is NULL it will cause undefined behavior.
* If the list is empty, it will cause undefined behavior. 
*
* @param:
* user_list:	a pointer to a sorted list.
* 
* @return:
* Returns data in the last node.
* 
* Time Complexity O(1)
*/
void *SortedLPopBack(sorted_l_t *list);

/*
* Description:
* Counts the number of nodes in user_list.
* If user_list is NULL it will cause undefined behavior. 
*
* @param:
* user_list:	a pointer to a sorted list.
* 
* @return:
* Returns the number of nodes in user_list.
* 
* Time Complexity O(n)
*/
size_t SortedLCount(const sorted_l_t *list);

/*
* Description:
* Checks if user_list is empty.
* If user_list is NULL it will cause undefined behavior. 
*
* @param:
* user_list:	a pointer to a sorted list.
* 
* @return:
* Returns 1 if user_list is empty
* Return 0 if user_list is not empty.
* 
* Time Complexity O(1)
*/
int SortedLIsEmpty(const sorted_l_t *list);

/*
* Description:
* Return the data in user_iter.
* If user_iter is invalidate it will cause undefined behavior. 
*
* @param:
* user_iter:	an iterator to a sorted list node.
* 
* @return:
* Returns the data in user_iter.
* 
* Time Complexity O(1)
*/
void *SortedLGetData(sl_iterator_t iter);

/*
* Description:
* Returns an iterator to the first node in user_list.
* If user_list is NULL it will cause undefined behavior.
* If user_list is empty, it will return an iterator
* to the end node of user_list. 
*
* @param:
* user_list:	a pointer to a sorted list.
* 
* @return:
* Return an iterator to the first node in user_list.
* 
* Time Complexity O(1)
*/
sl_iterator_t SortedLBegin(const sorted_l_t *list);

/*
* Description:
* Returns the next iterator of user_iter.
* If user_iter is the end node it will cause undefined behavior.
* If user_iter is invalidate it will cause undefined behavior. 
*
* @param:
* user_iter:	a pointer to a sorted list.
* 
* @return:
* Returns the next iterator of user_iter.
* 
* Time Complexity O(1)
*/
sl_iterator_t SortedLNext(sl_iterator_t iter);

/*
* Description:
* Returns the previous iterator of user_iter.
* If user_iter is the first node it will return 
* a beginning node which is used as a border to a list.
* and should not be modified or removed.
* If user_iter is a beginning node of a list it will 
* cause undefined behavior.
* If user_iter is invalidate it will cause undefined behavior. 
*
* @param:
* user_iter:	a pointer to a sorted list.
* 
* @return:
* Returns the previous iterator of user_iter.
* 
* Time Complexity O(1)
*/
sl_iterator_t SortedLPrev(sl_iterator_t iter);

/*
* Description:
* Returns an iterator to the end node in user_list.
* the end node is used as a border to the list and
* should not be removed or modified.
* If user_list is NULL it will cause undefined behavior. 
*
* @param:
* user_list:	a pointer to a sorted list.
* 
* @return:
* Return an iterator to the end node of user_list.
* 
* Time Complexity O(1)
*/
sl_iterator_t SortedLEnd(const sorted_l_t *list);

/*
* Description:
* Checks if iter1 is equal to iter2.
*
* @param:
* iter1:	an iterator to a sorted list node.
* iter2:	an iterator to a sorted list node.
*
* @return:
* Returns 1 if iter1 and iter2 are equal.
* Returns 0 if they are not equal.
* 
* Time Complexity O(1)
*/
int SortedLIsEqual(sl_iterator_t iter1, sl_iterator_t iter2);

/*
* Description:
* The function will traverse all nodes between from to to 
* iterators (not include to), and will return an iterator
* of a node for which the comparison function of user_list
* will return 0 for comparing its data with the data of param.
* If not found it will return the iterator to.
* If from or to are invalidate it will cause undefined behavior.
* If user_list is NULL it will cause undefined behavior. 
* If param is NULL it will cause undefined behavior.
* if from and to are not in the same list or from is not 
* located before to it will cause undefined behavior. 
*
* @param:
* from:			an iterator to a sorted list node.
* to:			an iterator to a sorted list node.
* user_list: 	a pointer to a sorted list.
* param:		a pointer to a data value.
*
* @return:
* Returns the iterator in which param's data is founded.
* Returns to iterator if param's data was not found. 
* 
* Time Complexity O(n)
*/
sl_iterator_t SortedLFind(sl_iterator_t from, sl_iterator_t to, const sorted_l_t *list, const void *param);

/*
* Description:
* The function will traverse all nodes between from and to 
* iterators (not include to), and will call operation function
* with each iterator's data and param as parameters. 
* operation function should be of type:
* int operation (void *data, void *param).
* The function will stop traversint the iterators once
* operation returned a non-zero value.
* If from or to are invalidate it will cause undefined behavior.
* if from and to are not in the same list or from is not 
* located before to it will cause undefined behavior. 
* If operation is NULL it will cause undefined behavior. 
* If param is NULL it will cause undefined behavior.
*
* @param:
* from:			an iterator to a sorted list node.
* to:			an iterator to a sorted list node.
* operation: 	a pointer to a function.
* param:		a pointer to a data value.
*
* @return:
* Returns a non-zero value if operation failed.
* Returns 0 if operation did not fail. 
* 
* Time Complexity O(n)
*/
int SortedLForEach(sl_iterator_t from, sl_iterator_t to, operation_func_t operation, void *param);

/*
* Description:
* The function will traverse all nodes between from and to 
* iterators (not include to), and will call is_match function
* with each iterator's data and param as parameters. 
* is_match function should be of type:
* int is_match (const void *first, const void *second).
* The function will stop traversing when is_match will
* returns 1, and will return the iterator for which
* is_match returned 1.
* If is_match returned 0 for all iterators it will returne
* to iterator.
* If from or to are invalidate it will cause undefined behavior.
* if from and to are not in the same list or from is not 
* located before to it will cause undefined behavior. 
* If is_match is NULL it will cause undefined behavior. 
* If param is NULL it will cause undefined behavior.
*
* @param:
* from:			an iterator to a sorted list node.
* to:			an iterator to a sorted list node.
* is_match: 	a pointer to a function.
* param:		a pointer to a data value.
*
* @return:
* Returns the iterator of a node for which
* is_match returned 1.
* Returns to iterator if there is no match
* and is_match returned 0 for all iterators.
* 
* Time Complexity O(n)
*/
sl_iterator_t SortedLFindIf(sl_iterator_t from, sl_iterator_t to, ismatch_func_t find, const void *param);

/*
* Description:
* Mreges src list into dest list while
* maintaing the order defined by dest list
* comparison function.
* after the merge src list will remain empty.
*
* @param:
* dest:			a pointer to a sorted list.
* src:			a pointer to a sorted list
* 
* Time Complexity O(n + m)
*/
void SortedLMerge(sorted_l_t *dest, sorted_l_t *src);

#endif /* __SORTED_L_H__ */
