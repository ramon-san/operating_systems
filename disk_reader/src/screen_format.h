// Define header file if not defined.
#ifndef screen_format_h
#define screen_format_h

// Import libraries to be used.
#include <curses.h>

// Import proprietary libraries to be used.
#include "mbr_reader.h"
#include "hfs_plus.h"

void print_mbr(mbr_register partitions[4], int *i, int u_in);

void print_volume_header(HFSPlusVolumeHeader info);

void print_int(int location, int to_print);

#endif