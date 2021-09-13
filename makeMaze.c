#include <stdio.h>
#include <stdlib.h>
#include "makeMaze.h"
#include "map.h"

/*function to extract intial layout of the maze from map.c*/
char** makeMaze(int*row, int*column, int goal[2], int player[2]){
    int i;  /*declare variables for for loop*/
    int j;
    int **maze =NULL; /*declare 2D array for storing the table from getMetadata()*/
    char **actualMap= NULL; /*declaring the 2D char array for storing the maze itself*/
    int metadataAmt;
    int mapRow;
    int mapCol;
    getMetadata(&maze, &metadataAmt, &mapRow, &mapCol);/*extract the table from the map.c and store in maze*/
    *row = mapRow; /* set pointers which will be sent to the main fucntion*/
    *column = mapCol;   /* set pointers which will be sent to the main fucntion*/
    actualMap = (char**)malloc(mapRow*sizeof(char*)); /* malloc heap memeory for the array of intial maze*/
    for (i = 0; i < mapRow; ++i){
        actualMap[i] = (char*)malloc(mapCol*sizeof(char)); /*freed in the main function*/
        for(j = 0; j < mapCol; ++j){
            actualMap[i][j] = ' ';
        }
    }
    for(j = 1; j < (mapCol-1); ++j){                        /*this code sets the boundary on the maze*/
        int dashrow = mapRow - 1;
        actualMap[0][j] = '-';
        actualMap[dashrow][j] = '-';
    }
    actualMap[0][0] = '#';      
    actualMap[mapRow-1][0] = '#';
    actualMap[0][mapCol-1] = '#';
    actualMap[mapRow-1][mapCol-1] = '#';
    for (i = 1; i < (mapRow-1); ++i){
        actualMap[i][0]= '|';
        actualMap[i][mapCol -1] = '|';
    }                                           /*border setting finished*/
    for (i = 0; i < metadataAmt; ++i){ /* creating the actual initial maze with the characters*/
        int x_coor;
        int y_coor;
        int type;
        x_coor = maze[i][0]; /* extracting the x coordinate*/
        y_coor = maze[i][1]; /* extracting the y coordinate*/
        type = maze[i][2]; /*extracting the type of charater(object)*/
        if (type == 0){
            actualMap[x_coor][y_coor] = '^';/* if type is 0 then its the player and inserting the ^ icon at the coodinates*/
            player[1] = y_coor;/*storing the plaer coordinates in the player array for while loop in the main*/
            player[0] = x_coor;
        }
        else if (type == 1){
            actualMap[x_coor][y_coor] = 'x';
            goal[0] = x_coor;/* if type is 1 then its the goal and inserting the ^ icon at the coodinates*/
            goal[1] = y_coor;/*storing the goal coordinates in the player array for while loop in the main*/
        }
        else
            actualMap[x_coor][y_coor] = 'o';/* same as above but with wall object*/
    }
    for(i = 0; i<metadataAmt; ++i){
        free(maze[i]);
        maze[i] = NULL;
    }
    free(maze);
    maze = NULL;
    return actualMap;
}
