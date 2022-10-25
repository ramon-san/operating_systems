// Define header file if not defined.
#ifndef screen_format_h
#define screen_format_h

// Import libraries to be used.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <curses.h>
#include <math.h>

void print_screen(char *map, int *offset, int fs, int *y_axis, int *x_axis, char *filename);
/**
* Function to print editor screen.
*
* @param map    Memory address of file we're editing.
* @param offset Position where we should start printing.
*
*/

char *make_line(char *base, int dir);
/**
* Function to create a line to print in our editor.
*
* @param base Memory map for file to edit.
* @param dir  File position as a multiple of 16.
*
* @return     Pointer to string containing created line.
*/

#endif