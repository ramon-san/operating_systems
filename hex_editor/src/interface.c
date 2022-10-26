#include "interface.h"
#include "screen_format.h"

int edit(char *filename) {
    int fd, fs, fr; // File controller variables (descriptor, size, and rows).
    int u_in = 0, y_axis = 0, x_axis = 9, offset = 0;
    char status_text[35];

    // Read file.
    char *map = map_file(filename, &fd, &fs);
    if (map == NULL) exit(EXIT_FAILURE);

    // Assign file rows we're using, one row every 16 bytes.
    fr = (int)ceil((float)fs/16);
    if (fr == 0) {
        printf("File can't be empty");
        exit(EXIT_FAILURE);
    }

    while(u_in != 27) {
        print_screen(map, &offset, fr, &y_axis, &x_axis, filename);
        sprintf(status_text, "Map address: %c -> %i", map[y_axis*16+(x_axis-57)], y_axis*16+(x_axis-57));
	    mvprintw(30, 0, status_text);
        move(y_axis, x_axis);
        refresh();

        //u_in = leeChar();
        u_in = getch();

        move_controller(u_in, &y_axis, &x_axis, &offset, map);
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
    *fd = open(filePath, O_RDWR);
    if (*fd == -1) {
    	perror("Error opening file.");
	    return(NULL);
    }

    // Map file.
    struct stat st;
    fstat(*fd, &st);
    *fs = st.st_size;

    char *map = mmap(0, *fs, PROT_READ | PROT_WRITE, MAP_SHARED, *fd, 0);
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
void move_controller(int u_in, int *y_axis, int *x_axis, int *offset, char *map) {
    // x_position = 0;

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
                if (u_in != 27) {
                    map[*y_axis*16+(*x_axis-57)] = (char)u_in;
                    *x_axis += 1;
                    if (*x_axis > 72) {
                        *x_axis = 57;
                        if (*y_axis < 24) {
                            *y_axis += 1;
                        } else *offset += 1;
                    }
                }
            } else {
                if ((u_in >= 48 && u_in <= 57) || (u_in >= 65 && u_in <= 70) || (u_in >= 97 && u_in <= 102)) {
                    // map[*y_axis * 16 + *x_axis - 16] = u_in; // Check this line.
                    // x_position = check_x_position(x_axis);
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

// int check_x_position(int x_axis) {
//     return 0;
// }

// int leeChar() {
//   int chars[5];
//   int ch,i=0;
//   nodelay(stdscr, TRUE);
//   while((ch = getch()) == ERR); /* Espera activa */
//   ungetch(ch);
//   while((ch = getch()) != ERR) {
//     chars[i++]=ch;
//   }
//   /* convierte a numero con todo lo leido */
//   int res=0;
//   for(int j=0;j<i;j++) {
//     res <<=8;
//     res |= chars[j];
//   }
//   return res;
// }
