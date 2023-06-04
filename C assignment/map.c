#include<stdlib.h>
#include"map.h"

/*  This file and the corresponding header file (map.c and map.h) contains a
    single function you can use to get some metadata that you need to create
    the 2D map array in the main function. 

    DO NOT add any new function here. We will test it with our own map.c
    when we mark it. DO NOT change the name of the function and the filename
    (getMetadata function,  map.c and map.h)
    
    If you want to make your own metadata for the map (e.g adding wall),
    you can modify the metadata table here. Once again, keep in mind that
    we will test your assignment with our own metadata. */

void getMetadata(int *** metadataTable, int * metadataAmount, int * mapRow, int * mapCol)
{
    int i;
    int ** table;

    *metadataAmount = 17;   /* amount of the objects in the playable area */
    *mapRow = 8;            /* The map row size you will create later */
    *mapCol = 10;           /* The map column size you will create later */

    /* Remember, the playable area would be only (mapRow-2) x (mapCol-2)
       due to map border at the edge */

    /* Now it is the time to malloc 2D metadata array */
    table = (int **) malloc(sizeof(int *) * (*metadataAmount));

    for(i = 0 ; i < (*metadataAmount) ; i++)
    {
        table[i] = (int *) malloc(sizeof(int) * 3);
    }
        /*  every metadataTable row always has 3 integers. These 3 numbers are:
            <mapRow_index> <mapCol_index> <object_code>

            This is the list of the object_code:
            0 -> Player (will always start facing up with char '^')
            1 -> Goal (char 'x')
            2 -> Wall (char 'o')

            For simplicity, you can assume the first two entries are
            always the player and the goal position.

            You can assume there is only 1 player and 1 goal.
        */
    
    /*  Normally we put a newline after semicolon,
        but this is just to make it easier to read the table entry.
        All indexing is based on the 0-based index (starts from 0) */
    table[0][0] = 6; table[0][1] = 3; table[0][2] = 0;
    table[1][0] = 1; table[1][1] = 8; table[1][2] = 1;
    table[2][0] = 1; table[2][1] = 7; table[2][2] = 2;
    table[3][0] = 2; table[3][1] = 1; table[3][2] = 2;
    table[4][0] = 2; table[4][1] = 3; table[4][2] = 2;
    table[5][0] = 2; table[5][1] = 7; table[5][2] = 2;
    table[6][0] = 3; table[6][1] = 3; table[6][2] = 2;
    table[7][0] = 3; table[7][1] = 7; table[7][2] = 2;
    table[8][0] = 4; table[8][1] = 2; table[8][2] = 2;
    table[9][0] = 4; table[9][1] = 3; table[9][2] = 2;
    table[10][0] = 4; table[10][1] = 4; table[10][2] = 2;
    table[11][0] = 4; table[11][1] = 5; table[11][2] = 2;
    table[12][0] = 4; table[12][1] = 7; table[12][2] = 2;
    table[13][0] = 5; table[13][1] = 4; table[13][2] = 2;
    table[14][0] = 5; table[14][1] = 7; table[14][2] = 2;
    table[15][0] = 6; table[15][1] = 2; table[15][2] = 2;
    table[16][0] = 6; table[16][1] = 4; table[16][2] = 2;   
    
    *metadataTable = table; /* assign the array to be used later in the calling function */

    /* remember, you need to free this 2D table at some point once you finish
       extracting its information to create your own 2D map array in
       the main function. */
}