//
//  draw.c
//  Snake_Game
//
//  Created by Andreea Bitlan on 20/12/22.
//

#include "draw.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>


#define COLS 60
#define ROWS 30

void renderTable(void){
    printf("┌");
    for (int i = 0; i < COLS; i++)
      printf("─");
    printf("┐\n");

    for (int j = 0; j < ROWS; j++) {
      printf("│");
      for (int i = 0; i < COLS; i++)
        printf("·");
      printf("│\n");
    }

    printf("└");
    for (int i = 0; i < COLS; i++)
      printf("─");
    printf("┘\n");

}

void printGameOver(void){
    printf("\e[%iB\e[%iC Game Over! ", ROWS / 2, COLS / 2 - 5);
    printf("\e[%iF", ROWS / 2);
    fflush(stdout);
    getchar();
}


void drawHead(int * y, int * x, int head){
    printf("\e[%iB\e[%iC▓", y[head] + 1, x[head] + 1);
    printf("\e[%iF", y[head] + 1);
    fflush(stdout);
}
