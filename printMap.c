#include <stdio.h>
#include <stdlib.h>
#include "printMap.h"
/*function to print every version of the maze after the character has bee nmovd*/
void printmaze(char** maze, int row, int col, int player[2], int visibility){
    int i,j;/*varualble for for loop*/
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
