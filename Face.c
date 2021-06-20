#define _CRT_SECURE_NO_WARNINGS
/* STAV FINZ 313588394 ------------------ HW3*/

/**************/
/*   Face.c   */
/**************/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Face.h"

//////////////////////////////////////////////////////////////
// initFace From String - "f __/__/___  __/___/___  ___/___/___" 
// Aim:		add a face to the array
// Input:	pointer to the array , the place in array  and the TEXT
// Output:	1 if succeeded
//////////////////////////////////////////////////////////////
int initFaceFromText(char* line, Face* pF, int place)
{
	char* n = strtok(line, " ");//cutting the 'f' from the line.
	pF[place].vertex = NULL;
	int count = 0;
	while (n != NULL)
	{
		n = strtok(NULL, " ");//cutting a form of -- ".../.../..." -- numbers instead of ...
		if (n == NULL)
			break;
		pF[place].vertex = (int*)realloc(pF[place].vertex,sizeof(int)*(count+1));//increase the vertex array
		if (!pF[place].vertex)
			return 0;
		sscanf(n, "%d", &pF[place].vertex[count]);//gettirng the first number from ".../.../..."
		count++;
	}
	pF[place].size = count;
	return 1;
}

//////////////////////////////////////////
// Save Face to Text File
// Aim:		Saving  Face's variables
// Input:	File's pointer ,pointer of array of Faces , place of the face in the array
// Output:	1 if succeeded , 0 if not
//////////////////////////////////////////
int saveFaceToFileText(FILE* fp, Face* pF,int place)
{
	if (!pF)
		return 0;
	fprintf(fp, "%d\n", pF[place].size);
	for (size_t i = 0; i < pF[place].size; i++)
		fprintf(fp, "%d ", pF[place].vertex[i]);
	fprintf(fp, "\n");
	return 1;
	
}

//////////////////////////////////////////
// Load Face from Text File
// Aim:		Loading  Face's variables
// Input:	File's pointer ,pointer of array of Faces , place of the face in the array
// Output:	1 if succeeded , 0 if not
//////////////////////////////////////////
int loadFaceFromFileText(FILE* fp, Face* pF, int place)
{
	if (!pF)
		return 0;
	if (fscanf(fp, "%d\n", &pF[place].size) != 1)
		return 0;
	pF[place].vertex = (int*)malloc(sizeof(int) * pF[place].size);
	if (!pF[place].vertex)
		return 0;
	for (int i = 0; i < pF[place].size; i++)
	{
		if (fscanf(fp, "%d", &pF[place].vertex[i]) != 1)
			return 0;
	}
	fscanf(fp, "\n");
	return 1;
}

//////////////////////////////////////////
// Save Face to Binary File
// Aim:		Saving  Face's variables
// Input:	File's pointer ,pointer of array of Faces , place of the face in the array
// Output:	1 if succeeded , 0 if not
//////////////////////////////////////////
int saveFaceToFileBin(FILE* fp, Face* pF, int place)
{
	if (!pF)
		return 0;
	fwrite(&pF[place].size, sizeof(int), 1, fp);
	for (int i = 0; i < pF[place].size; i++)
	{
		fwrite(&pF[place].vertex[i], sizeof(int), 1, fp);
	}
	return 1;
}

//////////////////////////////////////////
// Load Face from Binary File
// Aim:		Loading  Face's variables
// Input:	File's pointer ,pointer of array of Faces , place of the face in the array
// Output:	1 if succeeded , 0 if not
//////////////////////////////////////////
int loadFaceFromFileBin(FILE* fp, Face* pF, int place)
{
	if (!pF)
		return 0;
	fread(&pF[place].size, sizeof(int), 1, fp);
	pF[place].vertex = (int*)malloc(sizeof(int) * pF[place].size);
	for (int i = 0; i < pF[place].size; i++)
	{
		fread(&pF[place].vertex[i], sizeof(int), 1, fp);
	}
	return 1;
}

//////////////////////////////////////////
// Free Face  from space
// Aim:		Free  Face's variables by order - the vertexes id's, then the Face.
// Input:	pointer of array of Faces , place of the face in the array
// Output:	1 if succeeded , 0 if not
//////////////////////////////////////////
int freeFace(Face* pF, int place)
{
	if (!pF)
		return 0;
	free(pF[place].vertex);
	return 1;
}