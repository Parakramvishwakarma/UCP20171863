#include <stdio.h>
#include<termios.h>
#include "map.h"
#include<stdlib.h>
#include "terminal.h"

char** editmaze(char** maze, int row, int col, char command, int* player_x, int*player_y);
void printmaze(char** maze, int row, int col, int player[2], int visibility);
char** makeMaze(int *row, int *column, int goal[2], int player[2]);
int main(int argc, char* argv[]){
    char** map = NULL;
    int row;
    char command;
    int goal[2];
    int player[2];
    int col;
    map = makeMaze(&row, &col, goal, player);
    if (argc == 1){
        disableBuffer();
        system("clear");
        while (player[0] != goal[0] || player[1] != goal[1]){
            printmaze(map, row, col, player, 0);
            scanf(" %c", &command);
            map = editmaze(map, row, col, command, &player[0], &player[1]);
            system("clear");
        }
        printmaze(map, row, col, player, 0);
        printf("yaya you did it");
        enableBuffer();
    }
    else if (argc == 2){
        int visibility= atoi(argv[1]);
        disableBuffer();
        system("clear");
        while (player[0] != goal[0] || player[1] != goal[1]){
            printmaze(map, row, col, player, visibility);
            scanf(" %c", &command);
            map = editmaze(map, row, col, command, &player[0], &player[1]);
            system("clear");
        }
        printmaze(map, row, col, player, visibility);
        printf("yaya you did it");
        enableBuffer(); 
    }
    else{
        printf("ERROR ONLY ONE COMMAND LINE PARAMETER ALLOWED(1-10) APART FROM EXECUTABLE NAME ");
    }
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
void printmaze(char** maze, int row, int col, int player[2], int visibility){
    int i;
    int j;
    if (visibility == 0){
        for( i = 0; i < row; ++i){
            for( j =0; j < col; ++j){
                printf("%c", maze[i][j]);
            }
            printf("\n");
        } 
    }
    else{
        int x = player[0];
        int y = player[1];
        int lower_x = x-visibility;
        int upper_x = x + visibility;
        int upper_y = y + visibility;
        int lower_y = y - visibility;
        if (lower_x <0)
            lower_x = 0;
        if (upper_x >row-1)
            upper_x = row -1;
        if (upper_y> col -1)
            upper_y = col -1;
        if (lower_y < 0)
            lower_y = 0;
        
        for(x = 0; x < row; ++x){
            for(y = 0; y < col; ++y){
                if (x<= upper_x && x >= lower_x){
                    if (y <= upper_y && y >= lower_y){
                        printf("%c", maze[x][y]);
                    }
                    else
                        printf(" "); 
                        
                }
                else
                   printf(" ");
                   
            }
            printf("\n");
        }
    }
}

char** editmaze(char** maze, int row, int col, char command, int *player_x, int *player_y){
    int next[2];

    if (command =='a'){
        next[0] = *player_x;
        next[1] = *player_y -1;
        if(maze[next[0]][next[1]] == ' '){
            maze[*player_x][*player_y] = ' ';
            *player_x = next[0];
            *player_y = next[1];
            maze[*player_x][*player_y] = '<';
        }
        else if(maze[next[0]][next[1]] == 'x'){
            maze[*player_x][*player_y] = ' ';
            *player_x = next[0];
            *player_y = next[1];
            maze[*player_x][*player_y] = '<';
        }
        else if (maze[next[0]][next[1]] == 'o') {
            maze[*player_x][*player_y] = '<';
        }
        else{
           
             maze[*player_x][*player_y] = '<';
        }
    }
    else if (command == 'w'){
        next[0] = *player_x-1;
        next[1] = *player_y;
        if(maze[next[0]][next[1]] == ' '){
            maze[*player_x][*player_y] = ' ';
            *player_x = next[0];
            *player_y = next[1];
            maze[*player_x][*player_y] = '^';
        }
        else if(maze[next[0]][next[1]] == 'x'){
            maze[*player_x][*player_y] = ' ';
            *player_x = next[0];
            *player_y = next[1];
            maze[*player_x][*player_y] = '^';
        }
        else if(maze[next[0]][next[1]] == 'o'){
            maze[*player_x][*player_y] = '^';
        }
        else{
            maze[*player_x][*player_y] = '^';
        }
    }
    else if (command == 's'){
        next[0] = *player_x+1;
        next[1] = *player_y;
        if(maze[next[0]][next[1]] == ' '){
            maze[*player_x][*player_y] = ' ';
            *player_x= next[0];
            *player_y = next[1];
            maze[*player_x][*player_y] ='v';
        }
        else if(maze[next[0]][next[1]] == 'x'){
            maze[*player_x][*player_y] = ' ';
            *player_x= next[0];
            *player_y = next[1];
            maze[*player_x][*player_y] ='v';
        }
        else if(maze[next[0]][next[1]] == 'o'){
            maze[*player_x][*player_y] = 'v';
        }
        else{
            maze[*player_x][*player_y] = 'v';
        }
    }
    else if (command == 'd'){
        next[0] = *player_x;
        next[1] = *player_y +1;
        if(maze[next[0]][next[1]] == ' '){
            maze[*player_x][*player_y] = ' ';
            *player_x= next[0];
            *player_y = next[1];
            maze[*player_x][*player_y] ='>';
        }
        else if(maze[next[0]][next[1]] == 'x'){
            maze[*player_x][*player_y] = ' ';
            *player_x= next[0];
            *player_y = next[1];
            maze[*player_x][*player_y] ='>';
        }
        else if(maze[next[0]][next[1]] == 'o'){
            maze[*player_x][*player_y] = '>';
        }
        else{
            maze[*player_x][*player_y] = '>';
        }
    }
    else
        printf("ERROR in the input");
    return maze;
}
