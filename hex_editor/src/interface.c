#include "interface.h"

int edit(char *filename) {
    int fd, u_in = 0, y_axis = 0, x_axis = 9;
    
    while(u_in != 27) {
        // Read file.
        char *map = map_file(filename, &fd);
        if (map == NULL) {
            exit(EXIT_FAILURE);
        }
        // Create lines for editor screen.
        for(int i=0; i<25; i++) {
            // Create line, base, and offset.
            char *l = make_line(map, i*16);
            mvprintw(i, 0, l); // values are y-axis, x-axis, and content.
        }
        move(y_axis, x_axis);
        refresh();

        //read_char(&u_in);
        u_in = getchar();
        move_controller(u_in, &y_axis, &x_axis);
        // refresh();
        
        if (munmap(map, fd) == -1) {
            perror("Error while unmapping");
        }
        
        close(fd);
    }
    
    return 0;
}

/**
* Function to open file and map its memory.
*
* @param file_path Path for file we're trying to open.
* @param fd        File descriptor memory address for file to open.
*
* @return Memory map for file to edit.
*/
char *map_file(char *filePath, int *fd) {
    // Open file.
    *fd = open(filePath, O_RDONLY);
    if (*fd == -1) {
    	perror("Error opening file.");
	    return(NULL);
    }

    // Map file.
    struct stat st;
    fstat(*fd, &st);
    int fs = st.st_size;

    char *map = mmap(0, fs, PROT_READ, MAP_SHARED, *fd, 0);
    if (map == MAP_FAILED) {
    	close(*fd);
	    perror("Error mapping file.");
	    return(NULL);
    }

    return map;
}

/**
* Function to create a line to print in our editor.
*
* @param base Memory map for file to edit.
* @param dir  File position as a multiple of 16.
*
* @return     Pointer to string containing created line.
*/
char *make_line(char *base, int dir) {
	  char line[100];
	  int offset = 0;
	  // Print hexadecimal offset from file.
	  offset += sprintf(line, "%08x ", dir);
      // Loop to display values in hex.
	  for(int i=0; i < 4; i++) {
	  	unsigned char a,b,c,d;
		a = base[dir+4*i+0];
  		b = base[dir+4*i+1];
	  	c = base[dir+4*i+2];
		d = base[dir+4*i+3];
		offset += sprintf(&line[offset],"%02x %02x %02x %02x ", a, b, c, d);
	  }
      // Loop to display ascii representable format.
	  for(int i=0; i < 16; i++) {
          // Check if character is printable.
		  if (isprint(base[dir+i])) {
			  offset += sprintf(&line[offset], "%c", base[dir+i]);
		  }
		  else {
			  offset += sprintf(&line[offset],".");
		  }
	  }
	  sprintf(&line[offset],"\n");

  	return(strdup(line));
}

/**
* Function to read user input and parse result to binary.
*
* @param u_in Main user input variable memory address.
*
* @return Number for user input .
*/
int read_char(int *u_in) {
    int chars[5];
    int i=0;
    nodelay(stdscr, TRUE);
    while((*u_in = getch()) == ERR); // Active wait.
    ungetch(*u_in);
    while((*u_in = getch()) != ERR) {
        chars[i++]=*u_in;
    }
    // Converts to number with everything read.
    int res=0;
    for(int j=0; j<i; j++) {
        res <<= 8;
        res |= chars[j];
    }

    return res;
}

/**
* Function to move inside of the ncurses screen.
*
* @param u_in   User input to use.
* @param y_axis Curser current position in the y-axis.
* @param x_axis Curser current position in the x-axis.
*
*/
void move_controller(int u_in, int *y_axis, int *x_axis) {
    switch(u_in) {
        case(KEY_UP):
            *y_axis -= 1;
            break;
        case(KEY_RIGHT):
            *x_axis += 1;
            break;
        case(KEY_DOWN):
            *y_axis += 1;
            break;
        case(KEY_LEFT):
            *x_axis -= 1;
            break;
        default:
            if ((u_in >= 48 && u_in <= 57) || (u_in >= 65 && u_in <= 70) || (u_in >= 97 && u_in <= 102)) {
                // printw("%c", u_in);
                *x_axis += 1;
            }
            break;
	}
}