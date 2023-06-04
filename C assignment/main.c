#include "main.h"

int main(int argc, char* argv[])
{
	int*** dataTable = (int***) malloc(sizeof(int**));/*3D array, points to table*/ /* 8 bytes loss in memory */
	int** table = (int**) malloc(sizeof(int*));/*2D array*/			   /* 8 Bytes loss in memory*/
	char** map;/*2D array for map, pointer to char string*/
	char input = ' ';
	int dataAmount = 0;
	int mapRow = 0;
	int mapCol = 0;
	int result = 0;
	int i = 0;

	dataTable = &table;
	getMetadata(dataTable, &dataAmount, &mapRow, &mapCol);
	
	/*Create map's row and columns*/
	map = (char**) malloc(sizeof(char*) * mapRow);
	
	for(i = 0; i < mapRow; i++)
	{
		map[i] = (char*) malloc(sizeof(char) * (mapCol + 1)); /*each row contains mapCol + 1 columns, one extra for \0*/
	}
	
	/*Create map*/
	createMap(mapRow, mapCol, map);
	
	/*Create wall, player and goal*/
	createObjects(table, map, dataAmount);
	
	/*Print map*/
	disableBuffer();
	
	system("clear");
	displayMap(mapRow,mapCol,map);
	
	do
	{	
		scanf(" %c",&input);
		system("clear");
		movePlayer(table, map, input, &result);
		displayMap(mapRow,mapCol,map);
	}while(result != 1);
	
	printf("\nYou Win!");
	
	
	enableBuffer();
	
	/*dealloc*/
	freeMemory(map, dataTable, mapRow, dataAmount);

	return 0;
}

void displayMap(int mapRow, int mapCol, char**map)
{
	int i= 0;
	int j = 0;
	for(i = 0; i < mapRow; i++) 
	{
		for(j = 0; j < mapCol + 1; j++)
		{
			printf("%c",(map[i][j]));
		}
		printf("\n");
	}
}


void createMap(int mapRow, int mapCol, char** map)
{
	int i = 0;
	int j = 0;
	/*Initiate array wth spaces*/
	for(i = 0; i < mapRow; i++)
	{
		for(j = 0; j < mapCol; j++)
		{
			map[i][j] = ' ';
		}
	}
	
	map[0][0] = '#'; 
	map[0][mapCol - 1] = '#'; 
	map[mapRow - 1][0] = '#'; 
	map[mapRow - 1][mapCol - 1] = '#'; 
	
	
	
	/*display left right wall*/
	
	for(i = 1; i < mapRow - 1; i++) 
	{
		map[i][0] = '|';
		map[i][mapCol - 1] = '|';
	}
	
	/*display top bottom wall, from array[1] to array[8]*/
	
	for(i = 1; i < mapCol - 1; i++) 
	{	
		map[0][i] = '-';
		map[mapRow - 1][i] = '-';
	}
}

void createObjects(int** table, char** map, int dataAmount)
{
	int i = 0;
	int tableRow = 0;
	int tableCol = 0;
	for(i = 0; i < dataAmount; i++)
	{
		if(table[i][2] == 0) /*Player postion*/
		{
			tableRow = table[i][0];
			tableCol = table[i][1];
			map[tableRow][tableCol] =  '^';
		}
		
		if(table[i][2] == 1)
		{
			tableRow = table[i][0];
			tableCol = table[i][1];
			map[tableRow][tableCol] =  'x';
		}
		
		if(table[i][2] == 2)
		{
			tableRow = table[i][0];
			tableCol = table[i][1];
			map[tableRow][tableCol] =  'o';
		}
	}
}

void movePlayer(int** table, char** map , char input, int* result)
{		
	int pRow = 0;
	int pCol = 0;
	pRow = table[0][0];
	pCol = table[0][1];
	
	if(input == 'w')
	{
		if(map[pRow - 1][pCol] == ' ')
		{	
			map[pRow - 1][pCol] = '^';
			map[pRow][pCol] = ' ';
			table[0][0] = pRow - 1;
		}
		else if(map[pRow - 1][pCol] == 'x')
		{	
			map[pRow - 1][pCol] = '^';
			map[pRow][pCol] = ' ';
			*result = 1;
			table[0][0] = pRow - 1;
		}
		else
		{
			map[pRow][pCol] = '^';
		}
	}
	else if (input == 'a')
	{
		if(map[pRow][pCol - 1] == ' ')
		{
			map[pRow][pCol - 1] = '<';
			map[pRow][pCol] = ' ';
			table[0][1] = pCol - 1;
		}
		else if(map[pRow][pCol - 1] == 'x')
		{
			map[pRow][pCol - 1] = '<';
			map[pRow][pCol] = ' ';
			*result = 1;
			table[0][1] = pCol - 1;
		}
		else
		{
			map[pRow][pCol] = '<';
		}
	}
	else if (input == 's')
	{
		if(map[pRow + 1][pCol] == ' ')
		{
			map[pRow + 1][pCol] = 'v';
			map[pRow][pCol] = ' ';
			table[0][0] = pRow + 1;
		}
		else if(map[pRow + 1][pCol] == 'x')
		{
			map[pRow + 1][pCol] = 'v';
			map[pRow][pCol] = ' ';
			*result = 1;
			table[0][0] = pRow + 1;
		}
		else
		{
			map[pRow][pCol] = 'v';
		}
	}
	else if (input == 'd')
	{
		if(map[pRow][pCol + 1] == ' ')
		{
			map[pRow][pCol + 1] = '>';
			map[pRow][pCol] = ' ';
			table[0][1] = pCol + 1;
		}
		else if(map[pRow][pCol + 1] == 'x')
		{
			map[pRow][pCol + 1] = '>';
			map[pRow][pCol] = ' ';
			*result = 1;
			table[0][1] = pCol + 1;
		}
		else
		{
			map[pRow][pCol] = '>';
		}
	}
	


}

void freeMemory(char** map, int*** dataTable, int mapRow, int dataAmount)
{	
	int i = 0;
	/*deallocate memory*/
	for(i = 0; i < mapRow; i++) /*Free 2D map array pointer*/ 
	{
		free(map[i]);
	}
	free(map);  
	
	
	for(i = 0; i < dataAmount; i++) /*Free 3D data table*/
	{
		free(dataTable[0][i]);
	}
	free(dataTable[0]); 		
	
	dataTable = NULL;
	map = NULL;
}























