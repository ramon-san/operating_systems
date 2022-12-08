#include "mbr_reader.h"
#include "screen_format.h"
#include "hfs_plus.h"

int main(int argc, char const *argv[]) {
   int fd, fs;
   mbr_register partitions[4];
   int u_in = 0, c = 0, indexer = 0, screen = 0, file_counter = 0;
   int part_location = 0, catalog_location = 0, root_location = 0;
   char string[10];
   HFSPlusVolumeHeader vol_header;
   BTHeaderRec catalog_file;
   BTNodeDescriptor first_leaf;
   HFSPlusCatalogKey catalog_key;
   UInt32 start_block, block_size, file_offset = 0, file_type = 0; // Used to get catalog file.
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
                     part_location = move_to_partition(map, partitions[indexer]);
                     change_screen(&screen, 2, &u_in);
                  }
               } else break;
            case 2:
               vol_header = hfs_plus_info(map, part_location);
               if (u_in == 10) {
                  // For simplicity we'll only use the first extender (hardcoded).
                  start_block = BIG_ENDIAN_32(vol_header.catalogFile.extents[0].startBlock);
                  block_size = BIG_ENDIAN_32(vol_header.blockSize);
                  catalog_location = move_to_catalog_file(block_size, start_block, part_location);
                  catalog_location += sizeof(BTNodeDescriptor);
                  change_screen(&screen, 3, &u_in);
               } else {
                  print_volume_header(vol_header);
                  break;
               }
            case 3:
               catalog_file = catalog_file_info(map, catalog_location);
               if (u_in == 10) {
                  catalog_file.rootNode = BIG_ENDIAN_32(catalog_file.rootNode);
                  catalog_file.nodeSize = BIG_ENDIAN_16(catalog_file.nodeSize);
                  catalog_file.firstLeafNode = BIG_ENDIAN_32(catalog_file.firstLeafNode);
                  root_location = catalog_location-sizeof(BTNodeDescriptor)+(catalog_file.nodeSize*catalog_file.firstLeafNode);
                  change_screen(&screen, 4, &u_in);
                  u_in = 9;
               } else {
                  print_catalog_file(catalog_file, catalog_location-sizeof(BTNodeDescriptor));
                  break;
               }
            case 4:
               if (u_in == 10) {
                  change_screen(&screen, 5, &u_in);
               } else {
                  if (u_in == 9) {
                     mvprintw(9, 5, "File content:");
                     first_leaf = node_descriptor_info(map, root_location);
                     first_leaf.numRecords = BIG_ENDIAN_16(first_leaf.numRecords);
                     
                     print_first_leaf(first_leaf);

                     for (int i = 0; i < first_leaf.numRecords; i++) {
                        wchar_t file_info[255];
                        char file_text[300];

                        file_counter = root_location+catalog_file.nodeSize-i*2-2;
                        file_offset = BIG_ENDIAN_16(*((UInt16 *) &map[file_counter]));
                        catalog_key = catalog_key_info(map, root_location+file_offset);
                        catalog_key.nodeName.length = BIG_ENDIAN_16(catalog_key.nodeName.length);

                        for (int j = 0; j < catalog_key.nodeName.length; j++) {
                           file_info[j] = BIG_ENDIAN_16(catalog_key.nodeName.unicode[j]);
                        }
                        file_info[catalog_key.nodeName.length] = 0; // File ends with 0.
                        file_type = BIG_ENDIAN_16(*((UInt16 *) &map[root_location+file_offset+BIG_ENDIAN_16(catalog_key.keyLength)+2]));
                        sprintf(file_text, "- %i\t%x\t%ls", i, file_type, file_info);
                        mvprintw(11+i, 10, file_text);
                     }
                  }
                  break;
               }
            case 5:
               if (u_in == 10) {
                  screen = 6;
               } else {
                  mvprintw(2, 5, "Falta terminar esta pantalla...");
                  break;
               }
            default:
               printf("\nUnknown screen location (%d)...\n\n", screen);
               exit(EXIT_FAILURE);
               break;
         }
         refresh();
      }
   }
   endwin();
   return 0;
}
