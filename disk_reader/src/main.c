#include "my_curses.h"
#include "mbr_reader.h"

int main(int argc, char const *argv[]) {
   int fd, fs;
   mbr_register partitions[4];
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

   extract_mbr(map, partitions);

   do {
      mvprintw(2, 5, "Name");
      mvprintw(2, 20, "LBA");
      mvprintw(2, 35, "Size");

      for (int j=0; j < 4; j++) {
         char part_name[12], part_size[13], part_start[13];

         if (j == i) attron(A_REVERSE);
         
         sprintf(part_name, "Partition %d", j);
         mvprintw(4+j, 5, part_name);
         if (partitions[j].size + partitions[j].lba == 0) {
            sprintf(part_size, "NaN");
            sprintf(part_start, "NaN");
         } else {
            sprintf(part_size, "%d bytes", partitions[j].size);
            sprintf(part_start, "%d", partitions[j].lba);
         }
         mvprintw(4+j, 20, part_start);
         mvprintw(4+j, 35, part_size);
         
         attroff(A_REVERSE);
      }
      move(4+i, 5);
      refresh();
      c = read_char();
      if (c == 'Q') c = 'q';
      switch(c) {
         case 0x1B5B41: // Down arrow key.
            i = (i>0) ? i - 1 : 3;
            break;
         case 0x1B5B42: // Up arrow key.
            i = (i<3) ? i + 1 : 0;
            break;
         default:
            break; // Nothing 
      }
   } while (c != 'q');
   endwin();
   return 0;
}
