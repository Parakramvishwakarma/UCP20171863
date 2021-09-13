#include <stdio.h>
#include<termios.h>
#include "map.h"
#include<stdlib.h>
#include "terminal.h"
#include "makeMaze.h"
#include "printMap.h"

char** editmaze(char** maze, int row, int col, char command, int* player_x, int*player_y);
int main(int argc, char* argv[]){
    int i, x;
    char** map = NULL;  /* map variable to store the intial 2 array maze*/
    int row;    /* integer to store the amoiunt of rows in the maze*/
    char command; /* char variable to store the input*/
    int* goal; /* int array to store the goal cordinates*/
    int *player; /* int array to sotre the the player coordinates*/
    int col;    /* integer to store the amoiunt of cols in the maze*/
    player = (int*)malloc(sizeof(int)*2);
    goal  = (int*)malloc(sizeof(int)*2);
    map = makeMaze(&row, &col, goal, player); /* make intiial mazee from the getData function*/
    x = 1; /* set argc to one for the DEBUG conditional compilation*/
    #ifdef DARK 
    x = 2;   /* will be made 2 if DEBUG is defined hence allowing to reach the visibility*/
    #endif
    if (x == 1){
        if (argc == 2){
            printf("DARK MODE IS OFF, VISIBLITY SET TO DEFAULT 0");
        }
        disableBuffer();    /* buffer disabled*/
        system("clear");
        while (player[0] != goal[0] || player[1] != goal[1]){ /*loop that lasts while the character doesnt win*/
            printmaze(map, row, col, player, 0);
            scanf(" %c", &command); /*input from the player*/
            map = editmaze(map, row, col, command, &player[0], &player[1]); /*make the new map from editmaze also opdates the player array*/
            system("clear");
        }
        printmaze(map, row, col, player, 0);
        printf("yaya you did it");
        enableBuffer();
    }
    else if (x == 2){   /* if the DEBUG defined*/
        if (argc == 1)
            printf("DARK mode is on, please give visibility value");
        else{   
            int visibility= atoi(argv[1]);  /* convert the commandline visibility to integer*/
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
        
    }
    else{
        /*ERROR MESSAGE JUST INCASE*/
        printf("ERROR ONLY ONE COMMAND LINE PARAMETER ALLOWED(1-10) APART FROM EXECUTABLE NAME ");
    }
    for(i = 0; i < row; ++i){
        free(map[i]);
        map[i] = NULL;
    }
    free(goal);
    free(player);
    free(map);
    map = NULL;
    goal = NULL;
    player = NULL;
    return 0;

}

char** editmaze(char** maze, int row, int col, char command, int *player_x, int *player_y){
/* function to change the maze according to the commands by the user of w,a,s,d*/
    int next[2];/*2 int array to store coordinates of the next move*/
    if (command =='a'){             /*what to do if the command is 'a'*/
        next[0] = *player_x;    /*determine where the coordinates of the player after the move*/
        next[1] = *player_y -1;
        if(maze[next[0]][next[1]] == ' ' ){/* if/else set to check if we are allowed to move to the next step or its wall*/
            maze[*player_x][*player_y] = ' ';/* if allowed to move to the coordinates of the next[2] then make the old player coordinates ' '*/
            *player_x = next[0]; /*update player coodrinates*/
            *player_y = next[1];
            maze[*player_x][*player_y] = '<';/*change player symbol*/
        }
        else if(maze[next[0]][next[1]] == 'x'){
            maze[*player_x][*player_y] = ' ';
            *player_x = next[0];
            *player_y = next[1];
            maze[*player_x][*player_y] = '<';
        }
        else if (maze[next[0]][next[1]] == 'o') {/* if the obeject at next coordinate is 'o' then we cannot go there player remains at player[2] coordinates*/
            maze[*player_x][*player_y] = '<';/* player[2] --> coordinates of player arent updated they remain the same*/
        }
        else{  
             maze[*player_x][*player_y] = '<';
        }
    }
    else if (command == 'w'){/* repitition of the code above with a seperate command*/
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
