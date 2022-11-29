#include "mbr_reader.h"
#include "screen_format.h"

int main(int argc, char const *argv[]) {
   int fd, fs;
   mbr_register partitions[4];
   int u_in = 0, c = 0, indexer = 0, screen = 0;
   char string[10];
   initscr(); // Make standard screen (stdscr) for ncurses.
	cbreak();
	keypad(stdscr, TRUE);
	noecho();

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

   extract_mbr(map, partitions);

   while (u_in != 27) {
      if (screen == 0) {
         mvprintw(2, 5, "Welcome to the disk reader! Press [ENTER] to continue...");
         if (u_in == 10) {
            screen = 1;
            move(2, 0);
            clrtoeol();
            print_mbr(partitions, &indexer, u_in);
         }
      }
      u_in = getch();
      if (screen != 0) {
         switch (screen) {
            case 1:
               print_mbr(partitions, &indexer, u_in);
               break;
            default:
               break;
         }
         
      }
      // sprintf(string, "_ %i", u_in);
      // mvprintw(9, 5, string);
   }
   endwin();
   return 0;
}
