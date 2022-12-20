//
//  main.c
//  Snake_Game
//
//  Created by Andreea Bitlan on 19/12/22.
//


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>

#include "apples.h"
#include "draw.h"

#define COLS 60
#define ROWS 30

int hitHimself(int tail, int head, int *x, int *y){
    for (int i = tail; i != head; i = (i + 1) % 1000)
        if (x[i] == x[head] && y[i] == y[head]) return 1;
    return 0;
}
int checkIfNotDead(int *x, int *y, int head){
    if (x[head] == 1 || y[head] == 1 || x[head] == COLS-2 || y[head] == ROWS-2) return 1;
    return 0;
}
void playerInput(int *quit, int *xdir, int *ydir){
    struct timeval tv;
    fd_set fds;
    tv.tv_sec = 0;
    tv.tv_usec = 0;

    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
    if (FD_ISSET(STDIN_FILENO, &fds)) {
      int ch = getchar();
      if (ch == 27 || ch == 'q') {
        *quit = 1;
      } else if (ch == 'a' && *xdir != 1) {
        *xdir = -1;
        *ydir = 0;
      } else if (ch == 'd' && *xdir != -1) {
        *xdir = 1;
        *ydir = 0;
      } else if (ch == 's' && *ydir != -1) {
        *xdir = 0;
        *ydir = 1;
      } else if (ch == 'w' && *ydir != 1) {
        *xdir = 0;
        *ydir = -1;
      }
    }
}

int main() {
  // Hide cursor
  printf("\e[?25l");

  // Switch to canonical mode, disable echo
  struct termios oldt, newt;
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);

  int x[1000], y[1000];
  int quit = 0;
  while (!quit) {
      renderTable();
      printf("\e[%iA", ROWS + 2);//Move cursor back to top

    int head = 0, tail = 0;
    x[head] = COLS / 2;
    y[head] = ROWS / 2;
    int gameover = 0;
    int xdir = 1, ydir = 0;
    int applex = -1, appley = 0;
    int poisonx = -1, poisony = 0;
      quit = checkIfNotDead(x,y,head);
    while (!quit && !gameover) {
      if (applex < 0) {
          newApple(&applex, &appley, x, y, head, tail);
          quit = poisonedApple(&poisonx, &poisony, x, y, head, tail);
      }
        quit = checkIfNotDead(x,y,head);
        
      // Clear snake tail
      printf("\e[%iB\e[%iC·", y[tail] + 1, x[tail] + 1);
      printf("\e[%iF", y[tail] + 1);

      if (x[head] == applex && y[head] == appley) {applex = -1;printf("\a");} // Bell
        else tail = (tail + 1) % 1000;
        
      if (x[head] == poisonx && y[head] == poisony) gameover = 1;

      int newhead = (head + 1) % 1000;
      x[newhead] = (x[head] + xdir + COLS) % COLS;
      y[newhead] = (y[head] + ydir + ROWS) % ROWS;
      head = newhead;

        gameover=hitHimself(tail,head,x,y);
        
      
        drawHead(y,x,head);// Draw head
        usleep(5 * 1000000 / 60);
        playerInput(&quit, &xdir, &ydir);// Read keyboard
    }
      printGameOver();
  }
  // Show cursor
  printf("\e[?25h");
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  return 0;
}

