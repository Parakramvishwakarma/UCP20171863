#include <stdio.h>
#include<termios.h>
#include "map.h"
#include<stdlib.h>
#include "terminal.h"

char** editmaze(char** maze, int row, int col, char command, int* player_x, int*player_y);
void printmaze(char** maze, int row, int col);
char** makeMaze(int *row, int *column, int goal[2], int player[2]);
int main(void){
    char** map = NULL;
    int row;
    char command;
    int goal[2];
    int player[2];
    int col;

    map = makeMaze(&row, &col, goal, player);
    disableBuffer();
    while (player[0] != goal[0] || player[1] != goal[1]){
        scanf(" %c", &command);
        map = editmaze(map, row, col, command, &player[0], &player[1]);
        printmaze(map, row, col);
    }
    printf("yaya you did it");
    enableBuffer();
    return 0;

}
char** makeMaze(int*row, int*column, int goal[2], int player[2]){
    int i;
    int j;
    int **maze =NULL;
    char **actualMap;
    int metadataAmt;
    int mapRow;
    int mapCol;
    getMetadata(&maze, &metadataAmt, &mapRow, &mapCol);
    *row = mapRow;
    *column = mapCol;
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
        if (type == 0){
            actualMap[x_coor][y_coor] = '^';
            player[1] = y_coor;
            player[0] = x_coor;
        }
        else if (type == 1){
            actualMap[x_coor][y_coor] = 'x';
            goal[0] = x_coor;
            goal[1] = y_coor;
        }
        else
            actualMap[x_coor][y_coor] = 'o';
    }
    return actualMap;
}
void printmaze(char** maze, int row, int col){
    int i;
    int j;
    for( i = 0; i < row; ++i){
        for( j =0; j < col; ++j){
            printf("%c", maze[i][j]);
        }
        printf("\n");
    } 
}

char** editmaze(char** maze, int row, int col, char command, int *player_x, int *player_y){
    int next[2];

    if (command =='a'){
        next[0] = *player_x;
        next[1] = *player_y -1;
        printf("next =%d, %d", next[0], next[1]);
        printf("player =%d, %d", *player_x, *player_y);
        if(maze[next[0]][next[1]] == ' '){
            maze[*player_x][*player_y] = ' ';
            *player_x = next[0];
            *player_y = next[1];
            maze[*player_x][*player_y] = '<';
            printf("player: %d, %d", *player_x, *player_y);
        }
        else if(maze[next[0]][next[1]] == 'x'){
            maze[*player_x][*player_y] = ' ';
            *player_x = next[0];
            *player_y = next[1];
            maze[*player_x][*player_y] = '<';
            printf("player: %d, %d", *player_x, *player_y);
        }
        else if (maze[next[0]][next[1]] == 'o') {
            maze[*player_x][*player_y] = '<';
        }
        else{
           
             maze[*player_x][*player_y] = '<';
        }
        system("clear");
    }
    else if (command == 'w'){
        next[0] = *player_x-1;
        next[1] = *player_y;
        printf("next =%d, %d", next[0], next[1]);
        printf("player =%d, %d", *player_x, *player_y);
        if(maze[next[0]][next[1]] == ' '){
            maze[*player_x][*player_y] = ' ';
            *player_x = next[0];
            *player_y = next[1];
            maze[*player_x][*player_y] = '^';
            printf("player: %d, %d", *player_x, *player_y);
        }
        else if(maze[next[0]][next[1]] == 'x'){
            maze[*player_x][*player_y] = ' ';
            *player_x = next[0];
            *player_y = next[1];
            maze[*player_x][*player_y] = '^';
            printf("player: %d, %d", *player_x, *player_y);
        }
        else if(maze[next[0]][next[1]] == 'o'){
            maze[*player_x][*player_y] = '^';
        }
        else{
            maze[*player_x][*player_y] = '^';
        }
        system("clear");
    }
    else if (command == 's'){
        next[0] = *player_x+1;
        next[1] = *player_y;
        printf("next =%d, %d", next[0], next[1]);
        printf("player =%d, %d", *player_x, *player_y);
        if(maze[next[0]][next[1]] == ' '){
            maze[*player_x][*player_y] = ' ';
            *player_x= next[0];
            *player_y = next[1];
            maze[*player_x][*player_y] ='v';
            printf("player: %d, %d", *player_x, *player_y);
        }
        else if(maze[next[0]][next[1]] == 'x'){
            maze[*player_x][*player_y] = ' ';
            *player_x= next[0];
            *player_y = next[1];
            maze[*player_x][*player_y] ='v';
            printf("player: %d, %d", *player_x, *player_y);
        }
        else if(maze[next[0]][next[1]] == 'o'){
            maze[*player_x][*player_y] = 'v';
        }
        else{
            maze[*player_x][*player_y] = 'v';
        }
        system("clear");
    }
    else if (command == 'd'){
        next[0] = *player_x;
        next[1] = *player_y +1;
        printf("next =%d, %d", next[0], next[1]);
        printf("player =%d, %d", *player_x, *player_y);
        if(maze[next[0]][next[1]] == ' '){
            maze[*player_x][*player_y] = ' ';
            *player_x= next[0];
            *player_y = next[1];
            maze[*player_x][*player_y] ='>';
            printf("player: %d, %d", *player_x, *player_y);
        }
        else if(maze[next[0]][next[1]] == 'x'){
            maze[*player_x][*player_y] = ' ';
            *player_x= next[0];
            *player_y = next[1];
            maze[*player_x][*player_y] ='>';
            printf("player: %d, %d", *player_x, *player_y);
        }
        else if(maze[next[0]][next[1]] == 'o'){
            maze[*player_x][*player_y] = '>';
        }
        else{
            maze[*player_x][*player_y] = '>';
        }
        system("clear");
    }
    else{
        printf("ERROR in the input");
    }
    return maze;
}
