#pragma once
/* STAV FINZ 313588394 ------------------ HW3*/


/********************************************/
/*   Face.h                                 */
/*   a dynamic  Face with a header   */
/********************************************/
#include <stdio.h>

/*** Definitions ***/

// Face
typedef struct {
	int size;	// Number of vertexes of the face	
	int* vertex;	// Array of Ids of the vertexes
} Face;

/*** Function prototypes ***/
int initFaceFromText(char* line, Face* pF, int place);// initalize Face int array from TEXT

int saveFaceToFileText(FILE* fp, Face* pF,int place); // Saving Face to Text File
int loadFaceFromFileText(FILE* fp, Face* pF, int place);// Loading Face From Text File

int saveFaceToFileBin(FILE* fp, Face* pF, int place);// Saving Face to Binary File
int loadFaceFromFileBin(FILE* fp, Face* pF, int place);//Loading Face from Binary File

int freeFace(Face* pF, int place);// Free Face from space