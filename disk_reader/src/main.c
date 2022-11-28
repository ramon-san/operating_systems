#include "my_curses.h"
#include "mbr_reader.h"

int main(int argc, char const *argv[]) {
   int fd, fs;
   char *lista[] = {"Uno", "Dos", "Tres", "Cuatro" };
   int i = 0;
   int c;
   initscr();
   raw();
   noecho(); /* Don't show read character. */
   cbreak(); /* Make characters pass to the user. */

   /* File is given as a parameter. */
   if (argc != 2) {
     printf("Using %s <file> \n", argv[0]);
     return(-1);
   }

   // Read file.
   char *map = map_file((char *)argv[1], &fd, &fs);
   if (map == NULL) exit(EXIT_FAILURE);

   // Check that file contains MBR.
   if (check_mbr(map) == 0) {
      printf("\nFile doesn't have a MBR.\n\n");
      exit(EXIT_FAILURE);
   }

   extract_mbr(map);

   do {
      for (int j=0; j < 4; j++) {
         if (j == i) {
           attron(A_REVERSE);
         }
         mvprintw(5+j,5,lista[j]);
         attroff(A_REVERSE);
      }
      move(5+i,5);
      refresh();
      c = read_char();
      switch(c) {
         case 0x1B5B41:
            i = (i>0) ? i - 1 : 3;
            break;
         case 0x1B5B42:
            i = (i<3) ? i + 1 : 0;
            break;
         default:
            // Nothing 
            break;
      }
      move(10,5);
      printw("Estoy en %d: Lei %d",i,c);
      move(11,5);
      printw("Reading %c", map[i]);
   } while (c != 'q');
   endwin();
   return 0;
}
