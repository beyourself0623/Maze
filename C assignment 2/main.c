#include "main.h"

int main(int argc, char* argv[])
{
	
	if(argc != 2)
	{
		printf("Insert one parameter for the file\n");
	}
	else
	{
		FILE* fileName = NULL;
		fileName = fopen(argv[1],"r");
		
		if(fileName == NULL)
		{
			perror("Error opening file ");
		}
		else
		{
			int positionArray[3][2];
			int** table = NULL;
			char** map = NULL;
			char input = ' '; /*for user to input */
			int mapRow = 0;
			int mapCol = 0;
			int result = 0; 
			int totalObject; /*total object in the game*/
			int count = 0; /*to keep track with undo*/
			LinkedList* LL = NULL;
			
			LL = createLinkedList(); /*create linked list*/
			fscanf(fileName,"%d %d %d\n", &totalObject, &mapRow, &mapCol );
			positionArray[2][0] = mapRow;
			positionArray[2][1] = mapCol;
			
			/*create table 2D array*/
			table = createTable(totalObject, fileName, table);
			
			/*create map 2D array*/
			map = allocateMap(map, mapRow, mapCol);
			
			/*Create map*/
			createMap(mapRow, mapCol, map);

			createObjects(table, map, positionArray, totalObject);
			
			disableBuffer();
			system("clear");
			displayMap(mapRow, mapCol, map);
			
			do
			{	
				scanf(" %c",&input);
				system("clear");
				movePlayer(positionArray, map, input, &result, LL, &count); /*moveSnake is called inside movePlayer */
				displayMap(mapRow,mapCol,map);
			}while(result != 1 && result != 2);
			
			if(result == 1)
			{
				printf("\nYou Win!\n");
			}
			else if (result == 2)
			{
				printf("\nYou lose, try again.\n");
			}
			
			enableBuffer();

			freeLinkedList(LL, &freeNode); /*free linked list*/
			fclose(fileName);
			freeMemory(table, map, totalObject, mapRow);
			
		}/*end else*/
	}
	return 0;
}/*end main*/

int** createTable(int totalObject,FILE* fileName, int** table)
{
	int i;
	int j;
	table = (int**)malloc(totalObject * (sizeof(int*))); /*create 15 rows*/
	for(i = 0; i < totalObject; i++)
	{
		table[i] = (int*)malloc(3 * (sizeof(int))); /*create 3 columns*/
	}

	for(i = 0; i < totalObject; i++)
	{
		for(j = 0; j < 3; j++)
		{
			fscanf(fileName, "%d", &table[i][j]);
		}
		
	}

	return table;
}

char** allocateMap(char** map, int mapRow, int mapCol)
{
	int i;
	map = (char**)malloc(mapRow * (sizeof(char*))); 
	for(i = 0; i < mapRow; i++) 
	{
		map[i] = (char*)malloc(mapCol * sizeof(char));
	}

	return map;
}

void createObjects(int** table, char** map, int positionArray[3][2], int totalObject)
{
	int i = 0;
	int tableRow = 0;
	int tableCol = 0;
	
	for(i = 0; i < totalObject; i++)
	{
		if(table[i][2] == 0) /*Player postion*/
		{
			tableRow = table[i][0];
			tableCol = table[i][1];
			map[tableRow][tableCol] =  '^';
			positionArray[0][0] = tableRow;
			positionArray[0][1] = tableCol;
		}
		else if(table[i][2] == 1)/*snake*/
		{
			tableRow = table[i][0];
			tableCol = table[i][1];
			map[tableRow][tableCol] =  '~';
			positionArray[1][0] = tableRow;
			positionArray[1][1] = tableCol;
		}
		else if(table[i][2] == 2)/*goal*/
		{
			tableRow = table[i][0];
			tableCol = table[i][1];
			map[tableRow][tableCol] =  'x';
		}
		else if(table[i][2] == 3)
		{
			tableRow = table[i][0];
			tableCol = table[i][1];
			map[tableRow][tableCol] =  'o';
		}
		
	}
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
	
	
	for(i = 1; i < mapCol - 1; i++) 
	{	
		map[0][i] = '-';
		map[mapRow - 1][i] = '-';
	}
}

void movePlayer(int positionArray[3][2], char** map , char input, int* result, LinkedList* list, int* count)
{		
	int pRow = 0;
	int pCol = 0;
	int sRow = 0;
	int sCol = 0;
	char pSign = ' ';
	Position* pos;
	pRow = positionArray[0][0];
	pCol = positionArray[0][1];
	sRow = positionArray[1][0];
	sCol = positionArray[1][1];
	
	
	if(input == 'w')
	{
		if(map[pRow - 1][pCol] == ' ')
		{	
			map[pRow - 1][pCol] = '^';
			map[pRow][pCol] = ' ';
			positionArray[0][0] = pRow - 1;
			pos = (Position*)malloc(sizeof(Position));
			pos->pRow = pRow;
			pos->pCol = pCol;
			pos->pSign = '^';
			moveSnake(positionArray, map, result, pos);
			insertStart(list,pos);
		}
		else if(map[pRow - 1][pCol] == 'x')
		{	
			map[pRow - 1][pCol] = '^';
			map[pRow][pCol] = ' ';
			*result = 1;
			positionArray[0][0] = pRow - 1;
		}
		else if(map[pRow - 1][pCol] == '~')
		{	
			map[pRow][pCol] = ' ';
			*result = 2;
		}
		else
		{
			map[pRow][pCol] = '^';
			pos = (Position*)malloc(sizeof(Position));
			pos->pRow = pRow;
			pos->pCol = pCol;
			pos->pSign = '^';
			moveSnake(positionArray, map, result, pos);
			insertStart(list,pos);
		}
		*count += 1;
		
	}
	else if (input == 'a')
	{
		if(map[pRow][pCol - 1] == ' ')
		{
			map[pRow][pCol - 1] = '<';
			map[pRow][pCol] = ' ';
			positionArray[0][1] = pCol - 1;

			pos = (Position*)malloc(sizeof(Position));
			pos->pRow = pRow;
			pos->pCol = pCol;
			pos->pSign = '<';
			moveSnake(positionArray, map, result, pos);
			insertStart(list,pos);
		}
		else if(map[pRow][pCol - 1] == 'x')
		{
			map[pRow][pCol - 1] = '<';
			map[pRow][pCol] = ' ';
			*result = 1;
			positionArray[0][1] = pCol - 1;
		}
		else if(map[pRow][pCol - 1] == '~')
		{	
			map[pRow][pCol] = ' ';
			*result = 2;
		}
		else
		{
			map[pRow][pCol] = '<';
			pos = (Position*)malloc(sizeof(Position));
			pos->pRow = pRow;
			pos->pCol = pCol;
			pos->pSign = '<';
			moveSnake(positionArray, map, result, pos);
			insertStart(list,pos);
		}

		*count += 1;
	}
	else if (input == 's')
	{
		if(map[pRow + 1][pCol] == ' ')
		{
			map[pRow + 1][pCol] = 'v';
			map[pRow][pCol] = ' ';
			positionArray[0][0] = pRow + 1;

			pos = (Position*)malloc(sizeof(Position));
			pos->pRow = pRow;
			pos->pCol = pCol;
			pos->pSign = 'v';
			moveSnake(positionArray, map, result, pos);
			insertStart(list,pos);
		}
		else if(map[pRow + 1][pCol] == 'x')
		{
			map[pRow + 1][pCol] = 'v';
			map[pRow][pCol] = ' ';
			*result = 1;
			positionArray[0][0] = pRow + 1;
		}
		else if(map[pRow + 1][pCol] == '~')
		{	
			map[pRow][pCol] = ' ';
			*result = 2;
		}
		else
		{
			map[pRow][pCol] = 'v';
			pos = (Position*)malloc(sizeof(Position));
			pos->pRow = pRow;
			pos->pCol = pCol;
			pos->pSign = 'v';
			moveSnake(positionArray, map, result, pos);
			insertStart(list,pos);
		}

		*count += 1;
	}
	else if (input == 'd')
	{
		if(map[pRow][pCol + 1] == ' ')
		{
			map[pRow][pCol + 1] = '>';
			map[pRow][pCol] = ' ';
			positionArray[0][1] = pCol + 1;

			pos = (Position*)malloc(sizeof(Position));
			pos->pRow = pRow;
			pos->pCol = pCol;
			pos->pSign = '>';
			moveSnake(positionArray, map, result, pos);
			insertStart(list,pos);
		}
		else if(map[pRow][pCol + 1] == 'x')
		{
			map[pRow][pCol + 1] = '>';
			map[pRow][pCol] = ' ';
			*result = 1;
			positionArray[0][1] = pCol + 1;
		}
		else if(map[pRow][pCol + 1] == '~')
		{	
			map[pRow][pCol] = ' ';
			*result = 2;
		}
		else
		{
			map[pRow][pCol] = '>';
			pos = (Position*)malloc(sizeof(Position));
			pos->pRow = pRow;
			pos->pCol = pCol;
			pos->pSign = '>';
			moveSnake(positionArray, map, result, pos);
			insertStart(list,pos);
		}
		
		*count += 1;
	}
	else if(input == 'u' && *count > 0)
	{
		map[pRow][pCol] = ' ';
		map[sRow][sCol] = ' ';
		
		pos = removeStart(list); /*get undo data*/
		positionArray[0][0]= pos->pRow;
		positionArray[0][1]= pos->pCol;
		positionArray[1][0]= pos->sRow;
		positionArray[1][1]= pos->sCol;
		pSign = pos->pSign;
		
		pRow = positionArray[0][0]; /*assign undo data to positionArray*/
		pCol = positionArray[0][1];
		sRow = positionArray[1][0];
		sCol = positionArray[1][1];
		map[pRow][pCol] = pSign;
		map[sRow][sCol] = '~';
		*count -=1;
	}
}

void moveSnake(int positionArray[3][2], char** map, int* result, Position* pos)
{
	int pRow = 0;
	int pCol = 0;
    int sRow = 0;
    int sCol = 0;
    int mapRow = 0;
    int mapCol = 0;
	int startRow = 0;
	int startCol = 0;
	int endRow = 0;
	int endCol = 0;
	
	pRow = positionArray[0][0];
	pCol = positionArray[0][1];
    sRow = positionArray[1][0];
    sCol = positionArray[1][1];
    mapRow = positionArray[2][0];
    mapCol = positionArray[2][1];

	startRow = sRow - mapRow; /*area around snake*/
	startCol = sCol - mapCol; /*area around snake*/
	endRow = sRow + mapRow;   /*area around snake*/
	endCol = sCol + mapCol;   /*area around snake*/
	
    /*area detection*/
	if(startRow < 0)
	{
		startRow = 0;
	}
	if(startCol < 0)
	{
		startCol = 0;
	}
	if(endRow >= mapRow)
	{
		endRow = mapRow - 1;
	}
	if(endCol >= mapCol)
	{
		endCol = mapCol - 1;
	}

    if(sCol < pCol)/*snake at left, player at right, snake move right*/
    {
        if(map[sRow][sCol + 1] == ' ' ) /*if can move right*/
        {
            map[sRow][sCol + 1] = '~';
			map[sRow][sCol] = ' ';
			positionArray[1][1] = sCol + 1;
			
        }
        else if(map[sRow][sCol + 1] == '^' || map[sRow][sCol + 1] == '<' || map[sRow][sCol + 1] == '>' || map[sRow][sCol + 1] == 'v' ) /*player at right*/
        {
            map[sRow][sCol + 1] = '~';
			map[sRow][sCol] = ' ';
			*result = 2;
        }
        else /*right got wall, move down orup to find player to find player*/
        {
            if(sRow < pRow) /*player is below than snake*/
            {
                if(map[sRow + 1][sCol] == ' ')
                {
                    map[sRow + 1][sCol] = '~';
                    map[sRow][sCol] = ' ';
                    positionArray[1][0] = sRow + 1;
					
                }
            }
            else /*player is above snake*/
            {
                if(map[sRow - 1][sCol] == ' ')
                {
                    map[sRow - 1][sCol] = '~';
                    map[sRow][sCol] = ' ';
                    positionArray[1][0] = sRow - 1;
					
                }
            }   
        }
		
    }
    else if(pCol < sCol)/*snake at right, player at left, snake move left*/
    {
        if(map[sRow][sCol - 1] == ' ') /*if can move left*/
        {
            map[sRow][sCol - 1] = '~';
			map[sRow][sCol] = ' ';
			positionArray[1][1] = sCol - 1;
			
        }
        else if(map[sRow][sCol - 1] == '^' || map[sRow][sCol - 1] == '<' || map[sRow][sCol - 1] == '>' || map[sRow][sCol - 1] == 'v' ) /*player at left*/
        {
            map[sRow][sCol - 1] = '~';
			map[sRow][sCol] = ' ';
			positionArray[1][1] = sCol - 1;
            *result = 2;
        }
        else /*right got wall, move down orup to find player to find player*/
        {
            if(sRow < pRow) /*player is below than snake*/
            {
                if(map[sRow + 1][sCol] == ' ')
                {
                    map[sRow + 1][sCol] = '~';
                    map[sRow][sCol] = ' ';
                    positionArray[1][0] = sRow + 1;
                }
            }
            else /*player is above snake*/
            {
                if(map[sRow - 1][sCol] == ' ')
                {
                    map[sRow - 1][sCol] = '~';
                    map[sRow][sCol] = ' ';
                    positionArray[1][0] = sRow - 1;
                }
            }
                
        }
    }

    else if(pCol == sCol) /*same column*/
    {
        if(sRow < pRow) /*if player at down*/
        {
            if(map[sRow + 1][sCol] == ' ') /*if can move down*/
            {
                map[sRow + 1][sCol] = '~';
                map[sRow][sCol] = ' ';
                positionArray[1][0] = sRow + 1;
            }
            else if(map[sRow + 1][sCol] == '^' || map[sRow + 1][sCol] == '<' || map[sRow + 1][sCol] == '>' || map[sRow + 1][sCol] == 'v' ) /*player at down*/
            {
                map[sRow + 1][sCol] = '~';
                map[sRow][sCol] = ' ';
                positionArray[1][0] = sRow + 1;
                *result = 2;
            }
           
        }
        else /*player at up*/
        {
            if(map[sRow - 1][sCol] == ' ' ) /*if can move up*/
            {
                map[sRow - 1][sCol] = '~';
                map[sRow][sCol] = ' ';
                positionArray[1][0] = sRow - 1;
            }
            else if (map[sRow - 1][sCol] == '^' || map[sRow - 1][sCol] == '<' || map[sRow - 1][sCol] == '>' || map[sRow - 1][sCol] == 'v' ) /*player at up*/
            {
                map[sRow - 1][sCol] = '~';
                map[sRow][sCol] = ' ';
                positionArray[1][0] = sRow - 1;
                *result = 2;
            }
      
        }
    }
	pos->sRow = sRow;
	pos->sCol = sCol;
}

void freeMemory(int** table, char** map, int totalObject, int mapRow)
{
    int i;
    for(i = 0; i < totalObject; i++) /*free table*/
	{
		free(table[i]);
	}
    for(i = 0; i < mapRow; i++) /*free map*/
    {
        free(map[i]);
    }

    free(table);
    free(map);
}
