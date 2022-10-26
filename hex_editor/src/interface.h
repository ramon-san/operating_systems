// Define header file if not defined.
#ifndef interface_h
#define interface_h

// Import libraries to be used.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <curses.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <math.h>

int edit(char *filename);

char *map_file(char *filePath, int *fd, int *fs);
/**
* Function to open file and map its memory.
*
* @param file_path Path for file we're trying to open.
* @param fd        File descriptor memory address for file to open.
*
* @return Memory map for file to edit.
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

int change_bytes(int x_axis, int y_axis, long *byte_value, char u_in);

#endif