// Define header file if not defined.
#ifndef shared_memory_h
#define shared_memory_h

// Import libraries to be used.
#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

// Import proprietary libraries.
#include "styles.h"

int getSharedMemory(char *memory_name, int buffer_size);

void type_in_shared_memory(char *memory_name, int buffer_size, int fd);

void close_shared_memory(char *memory_name);

#endif