#pragma once
/* STAV FINZ 313588394 ------------------ HW3*/


/**************************************************************************/
/* Node.h                                                                  */
/* This file contains GENERAL definitions used in several data structures */
/**************************************************************************/

#include "Object.h"

// new types
typedef Object DATA;					// a type for data (easy to change)

// Node
typedef struct node
{
	DATA*	key;
	struct node* next;
}NODE;
