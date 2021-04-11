/******************************************************************************			 
 *                 Exercise: dll                                              *
 *                 Developer: Rafael 	       			                      *
 *                 Reviwer: Yonatan                                           *
*                 Date: 17.7.20 fun corona time...                            *
 *                                                                            *
 *     “CODE IS LIKE HUMOR, WHEN YOU HAVE TO EXPLAIN IT, IT'S BAD”            *
 *                                              Cory House                    *
 ******************************************************************************/

#ifndef __DLL_H__
#define __DLL_H__

#include <stddef.h> /* size_t  */


typedef struct dll dll_t;
typedef struct dnode dnode_t;
typedef dnode_t *diterator_t;

typedef  int (*is_match_t)(const void *data, const void *param);

typedef int (*operation_t)(void *data, void *param);




/********************* FUNCTIONS DECLARATIONS ***********************/
/* DESCRIPTION: O(1)
 * Creates a new list and returns a pointer to it.
 * To prevent memory leaks, use DllDestroy to remove list.
 * 
 *
 * @return:
 * 			Pointer to list upon success.
 *        	Pointer to NULL upon failure to
 *        	allocate memory.
 */

dll_t *DllCreate(void);

/* DESCRIPTION: O(n)
 * Frees the memory allocated for the list.
 * Free all the allocated memory of the nodes list.
 * Sets all pointer to the nodes to NULL.
 * 
 * @param:
 *
 * 			dll:	pointer to the list to be destroyed.
 *
 */


void DllDestroy(dll_t *dll);

/* DESCRIPTION: O(1)
 * 
 * In case of allocation error: O(n).
 * Inserts a new node to the list.
 * The new node will be added before the given iterator_t.
 * Using malloc to alocate memory for the list.
 *
 * @param:
 * 			where:	an iterator to the node before
 * 			which:	new node wiil be inserted.
 * 			data: 	a pointer to data of the new node.  
 * 
 * @return:     
 * 			Iterator to the new node.
 * 			in case of failure returns the DllEnd(list)             
 */	
diterator_t DllInsert(diterator_t where, void *data);  /* insert before */

/* DESCRIPTION: (O1)
 * 
 * Removes a node from the list 
 * If the given iterator is the SllEnd(list) the
 * result is undefined behavior. 
 * 
 * @param:
 * 			current:	iterator of the node argument to be removed.
 *  
 * @return:  
 * 			Iterator to the next node after the one
 * 			which has been removed.
 *
 */
diterator_t DllRemove(diterator_t current); /* return next */

/* DESCRIPTION: O(1)
 * Checks wether the list is empty or not
 * 
 * @param:
 * 			my_list:	a pointer to a list
 *  
 * @return:  
 * 			1 if the list is empty
 * 			0 if the list is not empty
 *         
 */
int DllIsEmpty(const dll_t *dll);

/* DESCRIPTION: O(n)
 * Counts number of elements in a list
 * 
 * @param:
 * 			my_list:	a pointer to a list
 *  
 * @return:  
 * 			Return the number of elements in a list
 *         
 */
size_t DllSize(const dll_t *dll);

/* DESCRIPTION: O(1)
 * Adds an elements to the front of the list
 * 
 * @param:
 * 			my_list:	a pointer to a list
 * 			data:	pointer to data to be saved on the node
 *  
 * @return:  
 * 			Return an iterator to the current inserted element
 *         
 */
diterator_t DllPushFront(dll_t *dll, void *data);

/* DESCRIPTION: O(1)
 * Removes an elements from the start of the list
 * 
 * @param:
 * 			my_list:	a pointer to a list
 * 			data:	pointer to data to be saved on the node
 *  
 * @return:  
 * 			Returns the data that been saved on removed element
 *         
 */
void *DllPopFront(dll_t *dll);

/* DESCRIPTION: O(1)
 * Adds an elements to the end of the list
 * 
 * @param:
 * 			my_list:	a pointer to a list
 * 			data:	pointer to data to be saved on the node
 *  
 * @return:  
 * 			Returns an iterator to the current inserted element
 *        
 */
diterator_t DllPushBack(dll_t *dll, void *data);

/* DESCRIPTION: O(1)
 * Removes an elements from the end of the list
 * 
 * @param:
 * 			my_list:	a pointer to a list
 * 			data:	pointer to data to be saved on the node
 *  
 * @return:  
 * 			Returns the data that been saved on removed element
 *         
 */
void *DllPopBack(dll_t *dll);

/*****************************************************************************/
/* DESCRIPTION:  O(n)
 * Looks for a given parameter in a specific range, can be used 
 * with any kind of data and compare functions corresponding to the data.
 * 
 * @param:
 * 			from:		Starting point to search from
 * 			to:			Ending point to search until (not included)
 * 			is_match:	Compare function
 * 			param:		Value to search for
 *
 * @return:
 * 			Returns the first match if found, otherwise returns NULL
 *
 */
diterator_t DllFind(diterator_t from, diterator_t to, is_match_t is_match, void *param); /* include fropm, not include to */

/* DESCRIPTION:  O(n)
 * Looks for a given parameter in a specific range, can be used 
 * with any kind of data and compare functions corresponding to the data.
 * Adds the found matches to a new list sent by user.
 * 
 * @param:
 * 			from:		Starting point to search from
 * 			to:			Ending point to search until (not included)
 * 			is_match:	Compare function
 * 			param:		Value to search for
 *			list:		New list for found elements
 *
 * @return:
 * 			Returns the number of successful matches
 *
 */
int DllMultiFind(diterator_t from, diterator_t to, is_match_t is_match, void *param, dll_t *dest); 

/* DESCRIPTION: O(n) 
 * Edits values in a specific range, can be used 
 * with any kind of data and functions corresponding to the data.
 * 
 * @param:
 * 			from:		Starting point to edit from
 * 			to:			Ending point to edit until (not included)
 * 			operation:	Edit function
 * 			param:		Value to manipulate the data
 *
 * @return:
 * 			Returns (0) if succeded all operations, any corresponding 
 * 			fail exit-status on failure
 *
 */
int DllForEach(diterator_t from, diterator_t to, operation_t operation, void *param); /* include fropm, not include to */

/* DESCRIPTION:  O(1)
 * Extracts range of elements from the list and appends it after
 * a given iterator.
 * 
 * @param:
 * 			where:		After which element to insert the segment
 * 			from:		Starting point of extraction
 * 			to:			Ending point of extraction (included)
 *
 * @return:
 * 			Returns an iterator to the element after inserted segment
 *
 */
diterator_t DllSplice(diterator_t where, diterator_t from , diterator_t to); /* splice after where */

/*************************************************************************************************/

/* DESCRIPTION: O(1) 
 * Retrives the first element of a list
 * 
 * @param:
 * 			my_list:	Address of the list	
 *
 * @return:
 * 			Iterator to the first item in the list
 *
 */
diterator_t DllBegin(const dll_t *dll); 

/* DESCRIPTION: O(1) 
 * Retrives the last node in the list (Dummy Tail Node)
 * 
 * @param:
 * 			my_list:	Address of the list	
 *
 * @return:
 * 			Iterator to the Dummy Tail node
 *
 */
diterator_t DllEnd(const dll_t *dll);

/* DESCRIPTION: O(1) 
 * Retrives the next element in the list after given iterator
 * 
 * @param:
 * 			my_iterator:	iterator to an element
 *
 * @return:
 * 			Iterator to the next element in the list
 *
 */
diterator_t DllNext(diterator_t diterator);

/* DESCRIPTION: O(1) 
 * Retrives the previous element in the list before given iterator
 * 
 * @param:
 * 			my_iterator:	iterator to an element
 *
 * @return:
 * 			Iterator to the previous element in the list
 *
 */
diterator_t DllPrev(diterator_t diterator);

/* DESCRIPTION: (O1)
 * Retrieves data from an element in the list
 *
 * @param:
 * 			my_iterator:    Iterator to the wanted elem
 *
 * @return:
 * 			Returns the data stored in the element
 *
 */
void *DllGetData(diterator_t current);

/*
* DESCRIPTION: O(1)
* Sets the data of the node pointed to by iterator to data.
* If the iterator points to NULL or to the dummy node the behavior is undefined.
* If data is a NULL pointer, a NULL value will be set at the position.
*
* @param:
* 			current:	diterator_t that points to the node to set.
* 			data:		void pointer to data to be set.
*
* @return:
* 			Returns the iterator to the modified node
*/
diterator_t DllSetData(diterator_t current, void *data);

/* DESCRIPTION: O(1) 
 * Checks wether two nodes has the same address
 * 
 * @param:
 * 			iter1:	iterator to an element
 *			iter2:	iterator to an element
 *
 * @return:
 * 			1 if the iterators has same address
 * 			0 if the iterators has defferent addresses
 *
 */
int DllIsSame(diterator_t ite1, diterator_t ite2);

#endif /* __DLL_H__ */


