#include <stdio.h>
#include "map.h"
#include<stdlib.h>
void makeMaze(void);
int main(void){
    makeMaze();
    return 0;
}
void makeMaze(void){
    int i;
    int j;
    int **maze =NULL;
    char **actualMap;
    int metadataAmt;
    int mapRow;
    int mapCol;
    getMetadata(&maze, &metadataAmt, &mapRow, &mapCol);
    actualMap = (char**)malloc(mapRow*sizeof(char*));
    for (i = 0; i < mapRow; ++i){
        actualMap[i] = (char*)malloc(mapCol*sizeof(char));
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
    }
    for (i = 0; i < metadataAmt; ++i){
        int x_coor;
        int y_coor;
        int type;
        x_coor = maze[i][0];
        y_coor = maze[i][1];
        type = maze[i][2];
        if (type == 0)
            actualMap[x_coor][y_coor] = '^';
        else if (type == 1)
            actualMap[x_coor][y_coor] = 'x';
        else
            actualMap[x_coor][y_coor] = 'o';
    }
    
    for( i = 0; i < mapRow; ++i){
        for( j =0; j < mapCol; ++j){
            printf("%c", actualMap[i][j]);
        }
        printf("\n");
    }

}
