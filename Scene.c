#define _CRT_SECURE_NO_WARNINGS
/* STAV FINZ 313588394 ------------------ HW3*/

/**************/
/*   Scene.c   */
/**************/
#include <stdarg.h>
#include<stdio.h>
#include<string.h>
#include "Scene.h"
#define SIZE_MAX 250

//////////////////////////////////////////////////////////////
// Create Scene
// Aim:		creating Scene from files - unknown how many files.
// Input:	Names of files.
// Output:	Returnig pointer of Scene or NULL.
//////////////////////////////////////////////////////////////
Scene* createScene(char* fileName, ...)
{
	va_list params;
	const char* name;
	va_start(params, fileName);
	name = fileName;
	Scene* pS = (Scene*)malloc(sizeof(Scene));
	if (!pS)
		return NULL;
	LIST* pL = (LIST*)malloc(sizeof(LIST));
	if (L_init(pL) == 0)
		return NULL;
	Object* pObj = (Object*)malloc(sizeof(Object));
	if (!pObj)
		return NULL;
	NODE* pN = &pL->head;
	while (name != NULL)
	{
		pObj = createObject(name);
		if (!pObj)
			return NULL;
		pN = L_insert(pN, pObj);
		name = va_arg(params,const char*);
	}
	va_end(params);
	pS->list = pL;
	return pS;
}

//////////////////////////////////////////////////////////////
// Perform
// Aim:		To print a result of Scene's Object function in the type required
// Input:	Pointer of the Scene, pointer to the function, string of type, string result
// Output:	Printing the String result.
//////////////////////////////////////////////////////////////
void perform(Scene* pS, void(*function)(Object*, void*), const char* type, const char* strToPrint)
{
	if (!pS)
	{
		printf("The SCENE is NULL\n");
		return;
	}
	void* typeOfReturnedData,*sum;
	int flag;
	if (strcmp(type, "INT") == 0) {
		typeOfReturnedData = malloc(sizeof(int));
		sum = malloc(sizeof(int));
		flag = 0;
	}
	else//The type is ---> DOUBLE
	{
		typeOfReturnedData = malloc(sizeof(double));
		sum = malloc(sizeof(double));
		flag = 1;
	}
	if (!typeOfReturnedData)
		return;
	NODE* p = pS->list->head.next;
	if (flag == 0)
		*((int*)sum) = 0;
	else
		*((double*)sum) = 0;
	while (p != NULL)
	{
		function(p->key, typeOfReturnedData);
		if (flag == 0)
			*((int*)sum) += *(int*)typeOfReturnedData;
		else
			*((double*)sum) += *(double*)typeOfReturnedData;
		p = p->next;
	}
	if (flag == 0)
		printf("%s  %d\n\n", strToPrint, *((int*)sum));
	else
		printf("%s  %lf\n\n", strToPrint, *((double*)sum));
}

//////////////////////////////////////////////////////////////
// Save Scene
// Aim:		To Save the scene into a File - Text OR Binary.
// Input:	Pointer of the Scene, File's Name , String type.
// Output:	prints if succeded or failed.
//////////////////////////////////////////////////////////////
void saveScene(Scene* pS, char* fileName, const char* type)
{
	if (!pS)
		return;
	FILE* fp;
	if (type == TextFormat)
	{
		fp = fopen(fileName, "w");
		int res = saveSceneIntoTextFile(fp, pS);
		if (res == 1)
			printf("Saved to TEXT FILE Successfully!! \n");
		else
			printf("Failed Saveing to TEXT FILE!!!!\n");
		fclose(fp);
	}
	else
	{
		fp = fopen(fileName, "wb");
		int res = saveSceneIntoBinFile(fp, pS);
		if (res == 1)
			printf("Saved to BIN FILE Successfully!! \n");
		else
			printf("Failed Saveing to BIN FILE!!!!\n");
		fclose(fp);
	}
	
}

//////////////////////////////////////////////////////////////
// Save Scene into Text File
// Aim:		To Save the scene into a Text File. 
// Input:	Pointer of the Scene, Pointer of file.
// Output:	1 if succeded , 0 failed.
//////////////////////////////////////////////////////////////
int saveSceneIntoTextFile(FILE* fp, Scene* pS)
{
	if (!pS)
		return 0;
	NODE* pN = pS->list->head.next;
	while (pN != NULL)
	{
		saveObjectToFileText(fp, pN->key);
		pN = pN->next;
	}
	return 1;
}

//////////////////////////////////////////////////////////////
// Load Scene
// Aim:		To load the scene from a File - Text OR Binary.
// Input:	File's Name , String type.
// Output:	Returns pointer of Scene OR NULL if failed ,prints if succeded or failed.
//////////////////////////////////////////////////////////////
Scene* loadScene(char* fileName, const char* type)
{
	Scene* pS = (Scene*)malloc(sizeof(Scene));
	if (!pS)
		return NULL;
	FILE* fp;
	if (type == TextFormat)
	{
		fp = fopen(fileName, "r");
		int res = loadSceneFromTextFile(fp, pS);
		if (res == 1)
			printf("Loaded Successfully!!\n");
		else
			printf("Failed Loading!!!!\n");
		fclose(fp);
	}
	else
	{
		fp = fopen(fileName, "rb");
		int res = loadSceneFromBinFile(fp, pS);
		if (res == 1)
			printf("Loaded Successfully!!\n\n");
		else
			printf("Failed Loading!!!!\n\n");
		fclose(fp);
	}
	return pS;
}

//////////////////////////////////////////////////////////////
// Load Scene from Text File
// Aim:		To load the scene from a Text File.
// Input:	Pointer of File , Pointer of Scene.
// Output:	Returns 1 if succeded or 0 if failed.
//////////////////////////////////////////////////////////////
int loadSceneFromTextFile(FILE* fp, Scene* pS)
{
	if (!pS)
		return 0;
	LIST* pL = (LIST*)malloc(sizeof(LIST));
	if (!pL)
		return 0;
	if (L_init(pL) == 0)
		return 0;
	Object* pObj ;
	NODE* pN = &pL->head;
	while (!feof(fp))
	{
		pObj = loadObjectFromFileText(fp);
		if (!pObj)
			return NULL;
		pN = L_insert(pN, pObj);
	}
	pS->list = pL;
	return 1;
}

//////////////////////////////////////////////////////////////
// Save Scene into Binary File
// Aim:		To Save the scene into a Binary File - Using a Helper know the length of list in the scene! --"findlength".
// Input:	Pointer of the Scene, Pointer of file.
// Output:	1 if succeded , 0 failed.
//////////////////////////////////////////////////////////////
int findLength(Scene* pS)//Finding the length of list in the Scene , returning the result.
{
	if (!pS)
		return -1;
	int size = 0;
	NODE* pN = pS->list->head.next;
	while (pN != NULL) 
	{
		size++;
		pN = pN->next;
	}
	return size;
}
int saveSceneIntoBinFile(FILE* fp, Scene* pS)
{
	if (!pS)
		return 0;
	int checkSceneLength = findLength(pS);//Getting how many Objects we have.
	if (checkSceneLength == -1)
		return 0;
	fwrite(&checkSceneLength, sizeof(int), 1, fp);
	NODE* pN = pS->list->head.next;
	int res;
	while (pN != NULL)
	{
		res = saveObjectToFileBin(fp, pN->key);
		if (res == 0)
			return 0;
		pN = pN->next;
	}
	return 1;
}

//////////////////////////////////////////////////////////////
// Load Scene from Binary File
// Aim:		To load the scene from a Binary File.
// Input:	Pointer of File , Pointer of Scene.
// Output:	Returns 1 if succeded or 0 if failed.
//////////////////////////////////////////////////////////////
int loadSceneFromBinFile(FILE* fp, Scene* pS)
{
	if (!pS)
		return 0;
	int size;
	fread(&size, sizeof(int), 1, fp);
	if (size == 0)
		return 0;
	LIST* pL = (LIST*)malloc(sizeof(LIST));
	if (!pL)
		return 0;
	if (L_init(pL) == 0)
		return 0;
	Object* pObj;
	NODE* pN = &pL->head;
	while (size != 0)
	{
		pObj = loadObjectFromFileBin(fp);
		if (!pObj)
			return NULL;
		pN = L_insert(pN, pObj);
		size--;
	}
	pS->list = pL;
	return 1;
}

//////////////////////////////////////////////////////////////
// Free Scene from Space
// Aim:		To free Scene varibales(definitions) by order - 
// the objects(the vertexes,the Faces,the Object), then nodes , then list, then Scene.
// Input:	Pointer of Scene.
// Output:	None.
//////////////////////////////////////////////////////////////
void freeScene(Scene* pS)
{
	int res = L_free(pS->list);
	if (res == 0)
		return;
	free(pS);
}