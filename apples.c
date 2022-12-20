//
//  apples.c
//  Snake_Game
//
//  Created by Andreea Bitlan on 20/12/22.
//

#include "apples.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>


#define COLS 60
#define ROWS 30

void newApple(int * applex, int *appley,int * x, int * y, int head, int tail){
    // Create new apple
    *applex = rand() % (COLS-1)+1;
    *appley = rand() % (ROWS-1)+1;

    for (int i = tail; i != head; i = (i + 1) % 1000)
      if (x[i] == *applex && y[i] == *appley)
          *applex = -1;

    if (*applex >= 0) {
      // Draw apple
      printf("\e[%iB\e[%iC❤", *appley + 1, *applex + 1);
      printf("\e[%iF", *appley + 1);
    }
}

int poisonedApple(int *applex, int *appley,int * x, int * y, int head, int tail){
    // Create new apple
    if (applex < 0){
        *applex = rand() % COLS;
        *appley = rand() % ROWS;
    }

    for (int i = tail; i != head; i = (i + 1) % 1000)
        if (x[i] == *applex && y[i] == *appley)return 1;
    if (applex >= 0) {
      // Draw apple
      printf("\e[%iB\e[%iC✇", *appley + 1, *applex + 1);
      printf("\e[%iF", *appley + 1);
    }
    return 0;
}
