// Define header file if not defined.
#ifndef screen_format_h
#define screen_format_h

// Import libraries to be used.
#include <curses.h>

// Import proprietary libraries to be used.
#include "mbr_reader.h"
#include "hfs_plus.h"

void print_mbr(mbr_register partitions[4], int *i, int u_in);
/**
 * Function to print MBR information to user and navigate as menu.
 * 
 * @param partitions    Array with MBR registers.
 * @param i             Index for curser.
 * @param u_in          Input from user.
 * 
 */

void print_volume_header(HFSPlusVolumeHeader info);
/**
 * Function to print basic HFS+ info.
 * 
 * @param info  Structure for HFS+ Volume Header.
 * 
 */

void print_catalog_file(BTHeaderRec info, int location);
/**
 * Function to print disk catalog file.
 * 
 * @param info      Fork data with catalog file information.
 * @param location  Memory address where this structure starts.
 * 
 */

void change_screen(int *screen, int number, int *u_in);
/**
 * Function to change screen number and clear screen.
 * 
 * @param screen    Memory address of screen varaible.
 * @param number    Number of screen to change to.
 * @param u_in      User input memory address.
 * 
 */

void print_first_leaf(BTNodeDescriptor info);
/**
 * Function to print first leaf node.
 * 
 * @param info      Node descriptor with root node information.
 * @param location  Memory address where this structure starts.
 * 
 */

void print_int(int location, int to_print);
/**
 * Function tu use in debug, prints int in given line as location.
 * 
 * @param location  Row in screen where we'll print.
 * @param to_print  Integer value we want to print.
 * 
 */

void print_hex(int location, int to_print);
/**
 * Function tu use in debug, prints int in given line as location.
 * 
 * @param location  Row in screen where we'll print.
 * @param to_print  Hex value we want to print.
 * 
 */

void string_uint16(char *text, UInt16 value);
/**
 * Function to pass UInt16 content to string.
 * 
 * @param text  Memory where text will be set.
 * @param value Integer value to set as text.
 * 
 */

#endif