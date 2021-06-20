
#pragma once
/* STAV FINZ 313588394 ------------------ HW3*/


/********************************************/
/*   Vertex.h                                 */
/*   a dynamic  Vertex with a header   */
/********************************************/
#include <stdio.h>

/*** Definitions ***/

// Vertex
typedef struct {
	float x; // Coordinates of Vertex
	float y;
	float z;
} Vertex;

/*** Function prototypes ***/
int initVertexFromText(char* line, Vertex* pV,int place); // intialize Vertex int array from TEXT

int saveVertexToFileText(FILE* fp, Vertex* pV,int place);// Save Vertex int Text File
int loadVertexFromFileText(FILE* fp, Vertex* pV, int place); // load Vertex from Text File

