#define _CRT_SECURE_NO_WARNINGS
/* STAV FINZ 313588394 ------------------ HW3*/

/**************/
/*   Vertex.c   */
/**************/
#include "Vertex.h"
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE_MAX 250

//////////////////////////////////////////
// Init Vertex From String - "V _____ ______ ______"
// Aim:		intialize  Vertex's variables
// Input:	String ,pointer of array of Vertexes , place of the vertex in the array
// Output:	1 if succeeded , 0 if not
//////////////////////////////////////////
int initVertexFromText(char* line, Vertex* pV, int place)
{
	//Making sure that we get 3 floats!
	if (sscanf(line, "%*s %f %f %f", &pV[place].x, &pV[place].y, &pV[place].z) != 3)
		return 0;
	return 1;
}

//////////////////////////////////////////
// Save Vertex to Text File
// Aim:		Saving  Vertex's variables
// Input:	File's pointer ,pointer of array of Vertexes , place of the vertex in the array
// Output:	1 if succeeded , 0 if not
//////////////////////////////////////////
int saveVertexToFileText(FILE* fp, Vertex* pV,int place)
{
	if (!pV)
		return 0;
	fprintf(fp, "%f %f %f\n",pV[place].x, pV[place].y, pV[place].z);
	return 1;
}

//////////////////////////////////////////
// Load Vertex from Text File
// Aim:		Loading  Vertex's variables
// Input:	File's pointer ,pointer of array of Vertexes , place of the vertex in the array
// Output:	1 if succeeded , 0 if not
//////////////////////////////////////////
int loadVertexFromFileText(FILE* fp, Vertex* pV, int place)
{
	if (!pV)
		return 0;
	fscanf(fp, "%f %f %f\n", &pV[place].x, &pV[place].y, &pV[place].z);
	return 1;
}