#include "mbr_reader.h"
#include "screen_format.h"
#include "hfs_plus.h"

int main(int argc, char const *argv[]) {
   int fd, fs;
   mbr_register partitions[4];
   int u_in = 0, c = 0, indexer = 0, screen = 0, location = 0;
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
               if (u_in == 10) {
                  if (partitions[indexer].size == 0) {
                     mvprintw(9, 5, "Empty partition, can't open.");
                     break;
                  } else {
                     location = move_to_partition(map, partitions[indexer]);
                     screen = 2;
                     u_in = 0;
                     clear();
                     // hfs_plus_info(map, location);
                  }
               } else break;
            case 2:
               if (u_in == 10) {
                  screen = 3;
               } else {
                  print_volume_header(hfs_plus_info(map, location));
                  break;
               }
            default:
               printf("\nUnknown screen location (%d)...\n\n", screen);
               exit(EXIT_FAILURE);
               break;
         }
         refresh();
      }
      // sprintf(string, "_ %i", u_in);
      // mvprintw(9, 5, string);
   }
   endwin();
   return 0;
}
