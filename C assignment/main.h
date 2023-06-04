#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include "terminal.h"
#include "string.h"
#include "map.h"

void displayMap(int mapRow, int mapCol, char**map);
void createObjects(int** table, char** map, int dataAmount);
void createMap(int mapRow, int mapCol, char** map);
void movePlayer(int** table, char** map , char input, int* result);
void freeMemory(char** map, int*** dataTable, int mapRow, int dataAmount);
void displayMapDark(int mapRow, int mapCol, char**map, int dark, int** table);
#endif
