#pragma once
/* STAV FINZ 313588394 ------------------ HW3*/


/********************************************/
/*   Object.h                                 */
/*   a dynamic  Object with a header   */
/********************************************/
#include "Vertex.h"
#include "Face.h"

/*** Definitions ***/

// Object
typedef struct {
	// Array of all Vertexes
	int numberOfVertexes;
	Vertex* vertexes;
	// Array of all Faces
	int  numberOfFaces;
	Face* faces;
} Object;

/*** Function prototypes ***/
void transformObject(char* originalObjectFileName, char* deformedObjectFileName);//Transform Object From Original To Deformed.

Object* createObject(char* filename);//Creating an Object.

void printFaces(Object* ptr, void* numberOfTriangularFaces);//Print how many triangular faces the object has.
void printVertexes(Object* ptr, void* numberOfVertexes);//Print how many vertexes the object has.

void getTotalArea(Object* ptr, void* totalAreaOfTriangularFaces);//Print the area of object.
double getAreaFromFace(Object* ptr,int i);//getting the area of a FACE. -- using " distance3D , heron "  to find the area.
double distance3D(double x1, double y1, double z1, double x2, double y2, double z2);//Helper to find area.
double heron(double a, double b, double c);//Helper to find area.

int saveObjectToFileText(FILE* fp, Object* pObj);//Saving an object to FILE TEXT.
Object* loadObjectFromFileText(FILE* fp); //Loading an object From TEXT FILE.

int saveObjectToFileBin(FILE* fp, Object* pObj);// Saving an Object to Binary File.
Object* loadObjectFromFileBin(FILE* fp);// Loading an Object From Binary File.

int freeObject(Object* pObj);// Free Object from space.