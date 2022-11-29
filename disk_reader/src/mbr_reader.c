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
void extract_mbr(char *file, mbr_register partitions[4]) {
    int pts = 0x1be; // Partition table start.
    
    for (int i = 0; i < 4; i++) {
        char file_start[11] = "0x", file_size[11] = "0x";
        mbr_register current_partition;
        pts += i*16;
        for (int j = 0; j < 4; j++) {
            char start_ch[3], size_ch[3]; 
            unsigned char a = file[pts+11-j], b = file[pts+15-j]; 
            sprintf(start_ch, "%02x", a);
            sprintf(size_ch, "%02x", b);
            strlcat(file_size, size_ch, sizeof(file_size));
            strlcat(file_start, start_ch, sizeof(file_start));
        }
        current_partition.lba = strtol(file_start, NULL, 16);
        current_partition.size = strtol(file_size, NULL, 16);
        
        partitions[i] = current_partition;
    }
}
