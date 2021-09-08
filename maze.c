#include <stdio.h>
#include<termios.h>
#include "map.h"
#include<stdlib.h>
#include "terminal.h"
#include "makeMaze.h"


char** editmaze(char** maze, int row, int col, char command, int* player_x, int*player_y);
void printmaze(char** maze, int row, int col, int player[2], int visibility);
/*char** makeMaze(int *row, int *column, int goal[2], int player[2]);*/
int main(int argc, char* argv[]){
    char** map = NULL;  /* map variable to store the intial 2 array maze*/
    int row;    /* integer to store the amoiunt of rows in the maze*/
    char command; /* char variable to store the input */
    int goal[2]; /* int array to store the goal cordinates*/
    int player[2]; /* int array to sotre the the player coordinates*/
    int col;    /* integer to store the amoiunt of cols in the maze*/
    map = makeMaze(&row, &col, goal, player); /* make intiial mazee from the getData function*/
    argc = 1; /* set argc to one for the DEBUG conditional compilation*/
    #ifdef DARK 
    argc = 2;   /* will be made 2 if DEBUG is defined hence allowing to reach the visibility*/
    #endif
    if (argc == 1){
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
    else if (argc == 2){   /* if the DEBUG defined*/
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
    else{
        /*ERROR MESSAGE JUST INCASE*/
        printf("ERROR ONLY ONE COMMAND LINE PARAMETER ALLOWED(1-10) APART FROM EXECUTABLE NAME ");
    }
    return 0;

}
/*function to print every version of the maze after the character has bee nmovd*/
void printmaze(char** maze, int row, int col, int player[2], int visibility){
    int i,j;
    if (visibility == 0){/*if the visibility is 0 means full view all map is printed*/
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
        int lower_x = x-visibility; /*depending on the visibility this coce determines what range of row and colimns to make visible*/
        int upper_x = x + visibility;
        int upper_y = y + visibility;
        int lower_y = y - visibility;
        if (lower_x <0)/* to avoid segmentation fault by accessing memory not allocated to us*/
            lower_x = 0;
        if (upper_x >row-1)
            upper_x = row -1;
        if (upper_y> col -1)
            upper_y = col -1;
        if (lower_y < 0)
            lower_y = 0;
        
        for(x = 0; x < row; ++x){   /*prints the only the part of the maze whcih is allowed to be visible according to commandline*/
            for(y = 0; y < col; ++y){
                if (x<= upper_x && x >= lower_x){
                    if (y <= upper_y && y >= lower_y){
                        printf("%c", maze[x][y]);
                    }
                    else
                        printf(" "); /*print a space where ever there is no visibility*/
                        
                }
                else
                   printf(" ");
                   
            }
            printf("\n");
        }
    }
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
