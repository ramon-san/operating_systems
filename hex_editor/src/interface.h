// Define header file if not defined.
#ifndef interface_h
#define interface_h

// Import libraries to be used.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>
#include <curses.h>
#include <sys/stat.h>
#include <sys/mman.h>

int edit(char *filename);

char *map_file(char *filePath, int *fd);
/**
* Function to open file and map its memory.
*
* @param file_path Path for file we're trying to open.
* @param fd        File descriptor memory address for file to open.
*
* @return Memory map for file to edit.
*/

void print_screen(char *map, int offset);
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

int read_char(int *u_in);
/**
* Function to read user input and parse result to binary.
*
* @param u_in Main user input variable memory address.
*
* @return Number for user input .
*/

void move_controller(int u_in, int *y_axis, int *x_axis, int *offset, char *map);
/**
* Function to move inside of the ncurses screen.
*
* @param u_in   User input to use.
* @param y_axis Curser current position in the y-axis.
* @param x_axis Curser current position in the x-axis.
* @param offset Value for the offset that indicates file line position.
*
*/

#endif