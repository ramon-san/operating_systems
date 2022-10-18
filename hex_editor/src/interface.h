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

char *make_line(char *base, int dir);

char *map_file(char *filePath, int *fd);

int read_char();

int edit(char *filename);

#endif