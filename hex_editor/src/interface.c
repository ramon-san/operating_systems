#include "interface.h"
#include "screen_format.h"

int edit(char *filename) {
    int fd, fs, fr; // File controller variables (descriptor, size, and rows).
    int u_in = 0, y_axis = 0, x_axis = 9, offset = 0;
    char u_in_ch;
        // Read file.
        char *map = map_file(filename, &fd, &fs);
        if (map == NULL) {
            exit(EXIT_FAILURE);
        }

    // Assign file rows we're using, one row every 16 bytes.
    fr = (int)ceil((float)fs/16);
    if (fr == 0) {
        printf("File can't be empty");
        exit(EXIT_FAILURE);
    }

    while(u_in != 27) {
        print_screen(map, &offset, fr, &y_axis, &x_axis, filename);
        move(y_axis, x_axis);
        refresh();

        //u_in_ch = read_char(&u_in);
        u_in = getch();
        u_in_ch = (char)u_in;
        printw("%c", u_in_ch);

        move_controller(u_in, u_in_ch, &y_axis, &x_axis, &offset, map);
    }

    if (munmap(map, fd) == -1) {
        perror("Error while unmapping");
    }
    close(fd);
    
    return 0;
}

/**
* Function to open file and map its memory.
*
* @param file_path Path for file we're trying to open.
* @param fd        File descriptor memory address for file to open.
* @param fs        File size we're reading.
*
* @return Memory map for file to edit.
*/
char *map_file(char *filePath, int *fd, int *fs) {
    // Open file.
    *fd = open(filePath, O_RDONLY);
    if (*fd == -1) {
    	perror("Error opening file.");
	    return(NULL);
    }

    // Map file.
    struct stat st;
    fstat(*fd, &st);
    *fs = st.st_size;

    char *map = mmap(0, *fs, PROT_READ, MAP_SHARED, *fd, 0);
    if (map == MAP_FAILED) {
    	close(*fd);
	    perror("Error mapping file.");
	    return(NULL);
    }

    return map;
}

/**
* Function to move inside of the ncurses screen.
*
* @param u_in   User input to use.
* @param y_axis Curser current position in the y-axis.
* @param x_axis Curser current position in the x-axis.
* @param offset Value for the offset that indicates file line position.
*
*/
void move_controller(int u_in, char u_in_ch, int *y_axis, int *x_axis, int *offset, char *map) {
    switch(u_in) {
        case(KEY_UP):
            if (*y_axis > 0) {
                *y_axis -= 1;
            } else *offset -= 1;
            break;
        case(KEY_RIGHT):
            if (*x_axis < 72) {
                *x_axis += 1;
                for (int i=1; i <= 16; i++) {
                    if (*x_axis == 8+i*3) {
                        *x_axis += 1;
                    }
                }
            } else *x_axis = 9;
            break;
        case(KEY_DOWN):
            if (*y_axis < 24) {
                *y_axis += 1;
            } else *offset += 1;
            break;
        case(KEY_LEFT):
            if (*x_axis > 9) {
                *x_axis -= 1;
                for (int i=1; i <= 16; i++) {
                    if (*x_axis == 8+i*3) {
                        *x_axis -= 1;
                    }
                }
            } else *x_axis = 72; // This is the final column of our editor.
            break;
        default:
            if (*x_axis >= 56 && *x_axis <= 72) {
                if (u_in != 27 && u_in < 65 && u_in > 68) {
                    map[*y_axis * 16 + *x_axis - 56] = u_in_ch;
                }
            } else {
                if ((u_in >= 48 && u_in <= 57) || (u_in >= 65 && u_in <= 70) || (u_in >= 97 && u_in <= 102)) {
                    // map[*y_axis * 16 + *x_axis - 16] = u_in; // Check this line.
                    if (*x_axis < 72) {
                        *x_axis += 1;
                        for (int i=1; i <= 16; i++) {
                            if (*x_axis == 8+i*3) {
                                *x_axis += 1;
                            }
                        }
                    } else *x_axis = 9;
                }
            }
            break;
	}
}
