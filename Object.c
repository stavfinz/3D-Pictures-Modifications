#define _CRT_SECURE_NO_WARNINGS
/* STAV FINZ 313588394 ------------------ HW3*/

/**************/
/*   Object.c   */
/**************/
#include "Object.h"
#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include<math.h>
#define SIZE_MAX 250

//////////////////////////////////////////////////////////////
// Trasform From Object
// Aim:		transform and Object From original File to deformed file - each x of vertex is multiplie by 0.3.
// Input:	File name of original, File name of Deformed.
// Output:	None.
//////////////////////////////////////////////////////////////
void transformObject(char* originalObjectFileName, char* deformedObjectFileName)
{
	FILE* fpOriginal = fopen(originalObjectFileName, "r");
	if (!fpOriginal)
	{
		printf("Failed open original...\n");
		return;
	}
	FILE* fpDeformed = fopen(deformedObjectFileName, "w");
	if (!fpDeformed)
	{
		printf("Failed open deformed...\n");
		return;
	}
	float x, y, z;
	char line[SIZE_MAX];
	fgets( line,SIZE_MAX, fpOriginal);
	while (!feof(fpOriginal))
	{
		if (line[0] == 'v' && line[1] == ' ')//found a vertex
		{
			sscanf(line, "%*s %f %f %f", &x, &y, &z);
			x *= 0.3;
			fprintf(fpDeformed,"%c  %f  %f  %f \n", 'v', x, y, z);
		}
		else 
		{
			fprintf(fpDeformed,"%s\n",line);//regular line
		}
		fgets(line, SIZE_MAX, fpOriginal);
	}
	fclose(fpOriginal);
	fclose(fpDeformed);
}

//////////////////////////////////////////////////////////////
// Create Object
// Aim:		Create an Object from file.
// Input:	File name.
// Output:	pointer of the object if succeded else NULL.
//////////////////////////////////////////////////////////////
Object* createObject(char* filename)
{
	FILE* fp = fopen(filename, "r");
	if (!fp)
	{
		printf("Failed open the file To create an OBJECT!\n");
		return NULL;
	}
	Object* pObj = (Object*)malloc(sizeof(Object));
	if (!pObj)
		return NULL;
	pObj->numberOfVertexes = 0;
	pObj->vertexes = NULL;
	pObj->numberOfFaces = 0;
	pObj->faces = NULL;
	char line[SIZE_MAX];
	fgets(line, SIZE_MAX, fp);
	while (!feof(fp))
	{
		if (line[0] == 'v' && line[1] == ' ')//found a Vertex
		{
			pObj->vertexes = (Vertex*)realloc(pObj->vertexes, sizeof(Vertex)*(pObj->numberOfVertexes+1));
			if (!pObj->vertexes)
				return NULL;
			if (initVertexFromText(line, pObj->vertexes, pObj->numberOfVertexes) == 0)// initalize vertex
				return NULL;
			pObj->numberOfVertexes++;
		}
		else if (line[0] == 'f') //found a Face
		{
			pObj->faces = (Face*)realloc(pObj->faces, sizeof(Face) *(pObj->numberOfFaces+1));
			if (!pObj->faces)
				return NULL;
			if (initFaceFromText(line, pObj->faces, pObj->numberOfFaces) == 0)// initialize Face
				return NULL;
			pObj->numberOfFaces++;
		}

		fgets(line, SIZE_MAX, fp);

	}
	fclose(fp);
	return pObj;
	
}

//////////////////////////////////////////////////////////////
// Print Faces
// Aim:		Find the number of triangular Faces in the Object.
// Input:	Pointer to Object, Pointer to the varibale to initialize with number.
// Output:	None.
//////////////////////////////////////////////////////////////
void printFaces(Object* ptr, void* numberOfTriangularFaces)
{
	int* count = (int*)numberOfTriangularFaces;
	*count = 0;
	for (int i = 0; i < ptr->numberOfFaces; i++)
	{
		if (ptr->faces[i].size == 3)
			*count = *count + 1;
	}
	*(int*)numberOfTriangularFaces = *count;
	printf("In this Object - the number of triangularFaces is: %d\n", *count);
}

//////////////////////////////////////////////////////////////
// Print Vertexes
// Aim:		Find the number of Vertexes in the Object.
// Input:	Pointer to Object, Pointer to the varibale to initialize with number.
// Output:	None.
//////////////////////////////////////////////////////////////
void printVertexes(Object* ptr, void* numberOfVertexes)
{
	*(int*)numberOfVertexes = ptr->numberOfVertexes;
	printf("In this Object - the number of all Vertexes is: %d\n", ptr->numberOfVertexes);
}

//////////////////////////////////////////////////////////////
// Get Total Area
// Aim:		Find the sum of :the area of all Triangular Faces in the Object.
// Input:	Pointer to Object, Pointer to the varibale to initialize with number.
// Output:	None.
//////////////////////////////////////////////////////////////
void getTotalArea(Object* ptr, void* totalAreaOfTriangularFaces)
{
	double* sum = (double*)totalAreaOfTriangularFaces;
	*sum = 0;
	for (int i = 0; i < ptr->numberOfFaces; i++)
	{
		if (ptr->faces[i].size == 3) 
		{
			*sum += getAreaFromFace(ptr,i);
		}
	}
	*(double*)totalAreaOfTriangularFaces = *sum;
	printf("In this Object - the total area of triangularFaces is: %f\n",*sum);
}

//////////////////////////////////////////////////////////////
// Get Area From Face - Using Helpers to find the Area - The Helpers : distance3D and heron.
// Aim:		Find the area of a Triangular Face in the Object.
// Input:	Pointer to Object, Place of Face in the array of Faces.
// Output:	the area found.
//////////////////////////////////////////////////////////////
double getAreaFromFace(Object* ptr,int i)
{
	int a, b, c;
	a = ptr->faces[i].vertex[0]-1;
	b = ptr->faces[i].vertex[1]-1;
	c = ptr->faces[i].vertex[2]-1;
	Vertex vA = ptr->vertexes[a];
	Vertex vB = ptr->vertexes[b];
	Vertex vC = ptr->vertexes[c];
	double disAB = distance3D(vA.x, vA.y, vA.z, vB.x, vB.y, vB.z);
	double disBC = distance3D(vB.x, vB.y, vB.z, vC.x, vC.y, vC.z);
	double disCA = distance3D(vC.x, vC.y, vC.z, vA.x, vA.y, vA.z);
	double area = heron(disAB, disBC, disCA);
	return area;
}
double distance3D(double x1, double y1, double z1, double x2, double y2, double z2)
{
	double disX = x1 - x2;
	double disY = y1 - y2;
	double disZ = z1 - z2;
	double a = pow(disX, 2) + pow(disY, 2) + pow(disZ, 2);
	double d = pow(a, 0.5);
	return d;
}
double heron(double a, double b, double c)
{
	double s = (a + b + c) / 2;
	double disA = s - a;
	double disB = s - b;
	double disC = s - c;
	double res = s * disA * disB * disC;
	double area = pow( res, 0.5);
	return area;
}

//////////////////////////////////////////
// Save Object to Text File
// Aim:		Saving  Object's variables(definitions) - first Vertexes then Faces.
// Input:	File's pointer ,pointer of Object.
// Output:	1 if succeeded , 0 if not
//////////////////////////////////////////
int saveObjectToFileText(FILE* fp, Object* pObj)//First Saving Vertexes, than Saving Faces.
{
	if (!pObj)
		return 0;
	fprintf(fp, "%d\n", pObj->numberOfVertexes);
	for (int i = 0; i < pObj->numberOfVertexes; i++)
	{
		saveVertexToFileText(fp, pObj->vertexes, i);
	}
	fprintf(fp, "%d\n", pObj->numberOfFaces);
	for (int i = 0; i < pObj->numberOfFaces; i++)
	{
		saveFaceToFileText(fp, pObj->faces, i);
	}
	return 1;

}

//////////////////////////////////////////
// Load Object from Text File
// Aim:		Loading  Object's variables(definitions) - first Vertexes then Faces.
// Input:	File's pointer.
// Output:	pointer of the object if succeded else NULL.
//////////////////////////////////////////
Object* loadObjectFromFileText(FILE* fp)//First loading Vertexes, than loading Faces.
{
	Object* pObj = (Object*)malloc(sizeof(Object));
	if (!pObj)
		return NULL;
	pObj->numberOfVertexes = 0;
	pObj->vertexes = NULL;
	pObj->numberOfFaces = 0;
	pObj->faces = NULL;
	if (fscanf(fp, "%d\n", &pObj->numberOfVertexes) != 1)
		return NULL;
	pObj->vertexes = (Vertex*)malloc(sizeof(Vertex) * pObj->numberOfVertexes);
	if (!pObj->vertexes)
		return NULL;
	for (int i = 0; i < pObj->numberOfVertexes; i++)
	{
		int res =loadVertexFromFileText(fp, pObj->vertexes, i);
		if (res == 0)
			return NULL;
	}
	if (fscanf(fp, "%d\n", &pObj->numberOfFaces) != 1)
		return NULL;
	pObj->faces = (Face*)malloc(sizeof(Face) * pObj->numberOfFaces);
	if (!pObj->faces)
		return NULL;
	for (int i = 0; i < pObj->numberOfFaces; i++)
	{
		int res =loadFaceFromFileText(fp, pObj->faces, i);
		if(res == 0)
			return NULL;
	}
	return pObj;
}

//////////////////////////////////////////
// Save Face to Binary File
// Aim:		Saving  Object's variables(definitions) - first Vertexes then Faces
// Input:	File's pointer ,pointer of Object.
// Output:	1 if succeeded , 0 if not
//////////////////////////////////////////
int saveObjectToFileBin(FILE* fp, Object* pObj)//First Vertexes then Faces!
{
	if (!pObj)
		return 0;
	fwrite(&pObj->numberOfVertexes, sizeof(int), 1, fp);
	fwrite(pObj->vertexes, sizeof(Vertex), pObj->numberOfVertexes, fp);
	fwrite(&pObj->numberOfFaces, sizeof(int), 1, fp);
	int res;
	for (size_t i = 0; i < pObj->numberOfFaces; i++)
	{
		res = saveFaceToFileBin(fp, pObj->faces, i);
		if (res == 0)
			return 0;
	}
	return 1;
}

//////////////////////////////////////////
// Load Object from Binary File
// Aim:		Loading  Object's variables(definitions) - first Vertexes then Faces
// Input:	File's pointer.
// Output:	pointer of the object if succeded else NULL.
//////////////////////////////////////////
Object* loadObjectFromFileBin(FILE* fp)
{
	Object* pObj = (Object*)malloc(sizeof(Object));
	if (!pObj)
		return NULL;
	fread(&pObj->numberOfVertexes, sizeof(int), 1, fp);
	pObj->vertexes = (Vertex*)malloc(sizeof(Vertex) * pObj->numberOfVertexes);
	if (!pObj->vertexes)
		return NULL;
	fread(pObj->vertexes, sizeof(Vertex), pObj->numberOfVertexes, fp);

	fread(&pObj->numberOfFaces, sizeof(int), 1, fp);
	pObj->faces = (Face*)malloc(sizeof(Face) * pObj->numberOfFaces);
	if (!pObj->faces)
		return NULL;
	int res;
	for (int i = 0; i < pObj->numberOfFaces; i++)
	{
		res = loadFaceFromFileBin(fp, pObj->faces, i);
		if (res == 0)
			return NULL;
	}
	return pObj;

}

//////////////////////////////////////////
// Free Object  from space
// Aim:		Free  Object's variables and then the Object by order - the verterxes , the faces , the object.
// Input:	pointer of Object.
// Output:	1 if succeeded , 0 if not
//////////////////////////////////////////
int freeObject(Object* pObj)
{
	if (!pObj)
		return 0;
	free(pObj->vertexes);
	int res;
	for (int i = 0; i < pObj->numberOfFaces; i++)
	{
		res =freeFace(pObj->faces, i);
		if (res == 0)
			return 0;
	}
	free(pObj->faces);
	free(pObj);
	return 1;
}