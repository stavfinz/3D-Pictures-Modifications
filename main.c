#define _CRT_SECURE_NO_WARNINGS
/* STAV FINZ 313588394 ------------------ HW3*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "Scene.h"
#define SIZE 3
int main()
{
	Scene* scene;
	Scene* scene1, * scene2;


	// Create a Scene of Objects received 
	// from files GoingMerry.obj, Donald.obj, Pony_cartoon.obj
	scene = createScene("GoingMerry.obj", "Donald.obj", "Pony_cartoon.obj", NULL);
	if (!scene)
	{
		printf("Error creating scene\n");
		return;
	}

	// Print out all Vertexes
	perform(scene, printVertexes, "INT", "The number of vertexes of all objects is");

	// Count the number of all Triangular faces of all objects in Scene 
	perform(scene, printFaces, "INT", "The number of Triangular faces of all objects is");

	// Count the total area of all Triangular faces of all objects in Scene 
	perform(scene, getTotalArea, "DOUBLE", "The total area of Triangular faces of all objects is");


	// Save the world to file in text and in binary formats
	saveScene(scene, "FirstScene.dat", TextFormat);
	saveScene(scene, "SecondScene.dat", BinaryFormat);

	// Retrieve the saved data
	scene1 = loadScene("FirstScene.dat", TextFormat);
	scene2 = loadScene("SecondScene.dat", BinaryFormat);

	// Check Retrieve the saved data of text format
	perform(scene1, printVertexes, "INT", "The number of vertexes of all objects is");
	perform(scene1, printFaces, "INT", "The number of Triangular faces of all objects is");
	perform(scene1, getTotalArea, "DOUBLE", "The total area of Triangular faces of all objects is");

	// Check Retrieve the saved data of binary format
	perform(scene2, printVertexes, "INT", "The number of vertexes of all objects is");
	perform(scene2, printFaces, "INT", "The number of Triangular faces of all objects is");
	perform(scene2, getTotalArea, "DOUBLE", "The total area of Triangular faces of all objects is");


	// Make transformation based on the original object defined in file Donald.obj
	transformObject("Donald.obj", "StrangeDonald.obj");

	freeScene(scene1);
	freeScene(scene2);
	freeScene(scene);


	system("pause");
}




