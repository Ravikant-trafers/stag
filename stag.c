// Define _XOPEN_SOURCE_EXTENDED for wide char functions in ncurses
#define _XOPEN_SOURCE_EXTENDED 1
// Include wide char version of ncurses
#include <ncursesw/ncurses.h>
// For setlocale to enable ncurses wide char
#include <locale.h>

// stdio for file I/O
#include <stdio.h>

#define HISTORY_SIZE 5

void print_values(float *values, int current_i) {
  // Print values to stdout, starting from one after newest (oldest) and
  // circle around to newest
  int i = current_i;
  for(i = current_i; i < current_i + HISTORY_SIZE; i++) {
    fprintf(stdout, "%.1f, ", values[i%HISTORY_SIZE]);
  }
  fprintf(stdout, "\n");
}

int main(int argc, char **argv) {
  int status = 1;
  int values_i = 0;
  float v;
  float values[HISTORY_SIZE];
  
  // Initialize ncurses
  int row, col;
  int ch;
  setlocale(LC_ALL, "");
  initscr();
  noecho();
  getmaxyx(stdscr,row,col);
  halfdelay(5);
  refresh();

  // Read floats to values, circle around after filling buffer 
  while(status != EOF) {
    status = fscanf(stdin, "%f\n", &v);
    if(status == 1) {
      values[values_i] = v;
      values_i = (values_i+1) % HISTORY_SIZE;
      // print_values(values, values_i);
      //fprintf(stdout, "%f\n", v);
    } else {
      //fprintf(stdout, "Error reading data (%d)\n", status);
    }
    
    ch = getch();
    if(ch == 'q')
      break;
    refresh();
  }

  endwin();

}
