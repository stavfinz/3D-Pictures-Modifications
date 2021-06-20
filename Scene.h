#pragma once
/* STAV FINZ 313588394 ------------------ HW3*/


/********************************************/
/*   Scene.h                                 */
/*   a dynamic  Scene with a header   */
/********************************************/
#include "Object.h"
#include "List.h"

/*** Definitions ***/

//Enum
enum FileType { TextFormat, BinaryFormat };

// Scene
typedef struct {
	// This structure contains a Single Direction Linked List of all objects in the Scene
	LIST* list;
} Scene;

/*** Function prototypes ***/
Scene* createScene(char* fileName, ...);//create Scene from files - unknown how many files.
void perform(Scene* pS,void(*function)(Object*,void*), const char* type, const char* strToPrint);//prints a result of Scene's Object function.

void saveScene(Scene* pS,char* fileName, const char* type);//saving Scene to Text or Binary FILE.
int saveSceneIntoTextFile(FILE* fp, Scene* pS);//saving to Text File.
Scene* loadScene(char* fileName, const char* type);//Loading Scene from Text or Binary FILE.
int loadSceneFromTextFile(FILE* fp, Scene* pS);//loading from Text File

int findLength(Scene* pS);//find the length of the List in Scene.
int saveSceneIntoBinFile(FILE* fp, Scene* pS);//saving to Binary File.
int loadSceneFromBinFile(FILE* fp, Scene* pS);//loading from Binary File.

void freeScene(Scene* pS);//Free Scene from Space.