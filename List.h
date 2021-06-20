#pragma once
/* STAV FINZ 313588394 ------------------ HW3*/


/********************************************/
/*   list.h                                 */
/*   a dynamic  linked list with a header   */
/********************************************/


#ifndef _LIST_
#define _LIST_

#include "Node.h"


/*** Definitions ***/

// List
typedef struct
{
	NODE head;
}LIST;


/*** Function prototypes ***/

int L_init(LIST* pList);					// create new list

NODE* L_insert(NODE* pNode, DATA* Value);	// add new node after *pNode

int L_delete(NODE* pNode);					// erase node after *pNode
 
int L_free(LIST* pList);					// free list memory

int L_print(LIST* pList);					// print the list content

#endif