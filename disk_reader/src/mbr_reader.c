#include "mbr_reader.h"

/**
* Function to open file and map its memory.
*
* @param file_path Path for file we're trying to open.
* @param fd        File descriptor memory address for file to open.
* @param fs        File size we're reading.
*
* @return Memory map for file to edit.
*/
char *map_file(char *file_path, int *fd, int *fs) {
    // Open file.
    *fd = open(file_path, O_RDWR);
    if (*fd == -1) {
    	perror("Error opening file");
	    return(NULL);
    }

    // Map file.
    struct stat st;
    fstat(*fd, &st);
    *fs = st.st_size;

    char *map = mmap(0, *fs, PROT_READ | PROT_WRITE, MAP_SHARED, *fd, 0);
    if (map == MAP_FAILED) {
    	close(*fd);
	    perror("Error mapping file");
	    return(NULL);
    }

    return map;
}

/**
* Function to check if given file is MBR based.
*
* @param file   Mapped memory for file in use.
*
* @return If successful 1 else 0.
*/
int check_mbr(char *file) {
    char signature[6];
    unsigned char a = file[510], b = file[511];

    sprintf(signature, "%02x %02x", a, b);
    if (!strcmp(signature, "55 aa")) {
        return 1;
    } else {
        return 0;
    }
}

/**
* Function to extract document information from MBR.
*
* @param file   Mapped memory for file in use.
*
* @return If successful 1 else 0.
*/
int extract_mbr(char *file) {
    return 0;
}