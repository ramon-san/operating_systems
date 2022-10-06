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

int getSharedMemory(char *name, int buffer_size);
/**
 * Function that creates a shared memory object.
 * 
 * @param memory_name Name of the memory object to create.
 * @param buffer_size Byte size assigned to the object.
 * 
 */

void type_in_shared_memory(char *name, int buffer_size, int fd);
/**
 * Function write into a shared memory object.
 * 
 * @param name		  Name of the conversation to write into.
 * @param buffer_size Byte size assigned to the object.
 * @param fd		  File descriptor for object we're using.
 * 
 */

void read_from_shared_memory(char *memory_name, int buffer_size, int fd);
/**
 * Function read from a shared memory object.
 * 
 * @param name		  Name of the conversation to read from.
 * @param buffer_size Byte size assigned to the object.
 * @param fd		  File descriptor for object we're using.
 * 
 */

void close_shared_memory(char *memory_name);
/**
 * Function to close shared memory object.
 * 
 * @param memory_name Name of the memory object to delete.
 *
 */

#endif