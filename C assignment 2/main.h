#ifndef MAIN_HEADER
#define MAIN_HEADER
#include <stdio.h>
#include <stdlib.h>
#include "terminal.h"
#include "LinkedList.h"
int** createTable(int totalObject,FILE* fileName, int** table);
char** allocateMap(char** map, int mapRow, int mapCol);
void createObjects(int** table, char** map, int positionArray[3][2], int totalObject);
void displayMap(int mapRow, int mapCol, char* *map);
void createMap(int mapRow, int mapCol, char** map);
void movePlayer(int positionArray[3][2], char** map , char input, int* result, LinkedList* LL, int* count);
void moveSnake(int positionArray[3][2], char** map, int* result, Position* pos);
void freeMemory(int** table, char** map, int totalObject, int mapRow);
#endif