#include "interface.h"
#include "screen_format.h"

int edit(char *filename) {
    int fd, fs;
    long fr; // File controller variables (descriptor, size, and rows).
    int u_in = 0, y_axis = 0, x_axis = 9, offset = 0, address, tt;
    char status_text[35], temp_str[20];

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
        move(y_axis, x_axis);
        refresh();

        u_in = getch();
        if (u_in == 9) {
            address = input_address();
            if (round(address/16) > fr) {
                attron(A_STANDOUT | A_UNDERLINE);
                mvprintw(30, 9, "Bad memory");
                attroff(A_STANDOUT | A_UNDERLINE);
            }
            else if (round(address/16) <= 24) {
                offset = 0;
            } else {
                offset = round(address/16)-24;
            }
            y_axis = 24;
            x_axis = 9;
        } else {
            move_controller(u_in, &y_axis, &x_axis, &offset, map);
        }
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
* Function to move inside of the ncurses screen.
*
* @param u_in   User input to use.
* @param y_axis Curser current position in the y-axis.
* @param x_axis Curser current position in the x-axis.
* @param offset Value for the offset that indicates file line position.
*
*/
void move_controller(int u_in, int *y_axis, int *x_axis, int *offset, char *map) {
    int x_position = 0;
    long byte_value = 0;

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
                    map[(*y_axis+*offset)*16+(*x_axis-57)] = (char)u_in;
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
                    x_position = change_bytes(*x_axis, *y_axis, &byte_value, (char)u_in);
                    
                    if (x_position == -1) {
                        printf("Error reading new position");
                        exit(EXIT_FAILURE);
                    }
                    map[(*y_axis+*offset)*16+x_position] = (char)byte_value;
                    
                    if (*x_axis < 56) {
                        *x_axis += 1;
                        if (*x_axis == 56) {
                            *x_axis = 9;
                            if (*y_axis < 24) {
                                *y_axis += 1;
                            } else *offset += 1;
                        }
                        for (int i=1; i <= 16; i++) {
                            if (*x_axis == 8+i*3) {
                                *x_axis += 1;
                            }
                        }
                    }
                }
            }
            break;
	}
}

/**
 * Function to change byte value if edited directly as hex value.
 * 
 * @param x_axis        Horizontal position.
 * @param y_axis        Vertical position.
 * @param byte_value    Memory position to save current byte value.
 * @param u_in          User input value.
 * 
 * @return New value for x position in screen.
 */
int change_bytes(int x_axis, int y_axis, long *byte_value, char u_in) {
    int x_value = -1, counter = 9;
    char complement, binary[3];

    for (int i=0; i<16; i++) {
        /* Condition if changing first position of hex. */
        if (x_axis == counter) {
            complement = (char)mvinch(y_axis, x_axis+1);
            sprintf(binary, "%c%c", u_in, complement);
            *byte_value = strtol(binary, NULL, 16);
            x_value = i;
        /* Condition if changing second position of hex. */
        } else if (x_axis == counter+1) {
            complement = (char)mvinch(y_axis, x_axis-1);
            sprintf(binary, "%c%c", complement, u_in);
            *byte_value = strtol(binary, NULL, 16);
            x_value = i;
        }
        counter += 3;
    }
    return x_value;
}

/**
 * Function to get user input for address change.
 * 
 * @return Decimal number with desired address.
 */
int input_address() {
    int u_in, flag = 1, location, counter = 0;
    char location_string[11] = "0x0";

    move(30, 0);
    clrtoeol();
    mvprintw(30, 0, "Move to: ");
    mvprintw(30, 9, location_string);
    move(30, 19);
    while (flag) {
        move(30, 11+counter);
        u_in = getch();
        if ((u_in >= 48 && u_in <= 57) || (u_in >= 65 && u_in <= 70) || (u_in >= 97 && u_in <= 102)) {
            printw("%c", (char)u_in);
            location_string[3+counter] = (char)u_in;
            counter++;
        }
        location = strtol(location_string, NULL, 16);
        if ((location >= 0 && u_in == 10) || counter == 8) flag = 0;
    }
    return location;
}
