#include "my_curses.h"

/**
 * Function to get user input.
 * 
 * @return Number for pressed character.
 * 
 */
int read_char() {
  int chars[5];
  int ch, i = 0;
  nodelay(stdscr, TRUE);
  while((ch = getch()) == ERR); /* Active wait. */
  ungetch(ch);
  while((ch = getch()) != ERR) {
    chars[i++] = ch;
  }
  /* Convert to number with everything read. */
  int res=0;
  for (int j=0; j < i; j++) {
    res <<=8;
    res |= chars[j];
  }
  return res;
}
