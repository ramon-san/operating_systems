// Define header file if not defined.
#ifndef mbr_reader_h
#define mbr_reader_h

// Import libraries to be used.
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>

typedef struct mbr_register {
    int lba; // Logical Block Address of the start sector.
    int size;
} mbr_register;

char *map_file(char *file_path, int *fd, int *fs);
/**
* Function to open file and map its memory.
*
* @param file_path Path for file we're trying to open.
* @param fd        File descriptor memory address for file to open.
* @param fs        File size we're reading.
*
* @return Memory map for file to edit.
*/

int check_mbr(char *file);
/**
* Function to check if given file is MBR based.
*
* @param file   Mapped memory for file in use.
*
* @return If successful 1 else 0.
*/

void extract_mbr(char *file, mbr_register partitions[4]);
/**
* Function to extract document information from MBR.
*
* @param file   Mapped memory for file in use.
*
* @return If successful 1 else 0.
*/

#endif