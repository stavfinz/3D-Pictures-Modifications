#define _CRT_SECURE_NO_WARNINGS
/* STAV FINZ 313588394 ------------------ HW3*/

/**************/
/*   list.c   */
/**************/


#include <stdio.h>
#include <stdlib.h>
#include "list.h"


//////////////////////////////////////////
// Init
// Aim:		create new list
// Input:	pointer to the list structure
// Output:	TRUE if succeeded
//////////////////////////////////////////
int L_init(LIST* pList)
{
	if (pList == NULL)
		return 0;	// no list to initialize

	pList->head.next = NULL;
	return 1;
}


/////////////////////////////////////////////////////////////////
// Insert
// Aim:		add new node
// Input:	pointer to the node BEFORE the place for the new one
//			a value to be stored in the new node
// Output:	pointer to the new node
/////////////////////////////////////////////////////////////////
NODE* L_insert(NODE* pNode, DATA* Value)
{
	NODE* tmp;

	if (!pNode)
		return NULL;

	tmp = (NODE*)malloc(sizeof(NODE));	// new node

	if (tmp != NULL) 
	{
		tmp->key = Value;
		tmp->next = pNode->next;
		pNode->next = tmp;
	}
	return tmp;
}


//////////////////////////////////////////////////////////////
// Delete
// Aim:		erase node
// Input:	pointer to the node BEFORE the node to be deleted 
// Output:	TRUE if succeeded
//////////////////////////////////////////////////////////////
int L_delete(NODE* pNode)
{
	NODE* tmp;
	if (!pNode)
		return 0;
	tmp = pNode->next;
	if (!tmp)
		return 0;
	pNode->next = tmp->next;
	int res =freeObject(tmp->key);
	if (res == 0)
		return 0;
	free(tmp);
	return 1;
}




////////////////////////////////////////////////
// Free (additional function)
// Aim:		free the list memory
// Input:	pointer to the list structure
// Output:	TRUE if succeeded
////////////////////////////////////////////////
int L_free(LIST* pList)
{
	NODE* tmp;
	int cont = 1;
	if (!pList)
		return 0;

	tmp = &(pList->head);
	while (cont)
		cont = L_delete(tmp);

	return 1;
}


////////////////////////////////////////////////
// Print (additional function)
// Aim:		print the list content (assume the DATA is int)
// Input:	pointer to the list structure
// Output:	a number of the printed elements
////////////////////////////////////////////////
//int L_print(LIST* pList)
//{
//	NODE* tmp;
//	int		c = 0;
//
//	if (!pList)
//		return 0;
//
//	printf("\n");
//	tmp = pList->head.next;
//	while (tmp != NULL)
//	{
//		printObject(&tmp->key);
//		c++;
//		tmp = tmp->next;
//	}
//	printf("\n");
//	return c;
//}