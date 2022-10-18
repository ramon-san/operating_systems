#include "interface.h"

int edit(char *filename) {
    int fd;

    // Read file.
    char *map = map_file(filename, &fd);
    if (map == NULL) {
        exit(EXIT_FAILURE);
    }
    
    for(int i=0; i<25; i++) {
      	// Create line, base, and offset.
    	char *l = make_line(map, i*16);
	    mvprintw(i, 0, l); // values are y-axis, x-axis, and content.
    }
    refresh();

    read_char();

    if (munmap(map, fd) == -1) {
        perror("Error while unmapping");
    }
    close(fd);
    
    return 0;
}

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

char *make_line(char *base, int dir) {
	  char linea[100]; // The line is smaller
	  int offset = 0;
	  // Show 16 chars per line
	  offset += sprintf(linea, "%08x ", dir); // Offset in hexadecimal
	  for(int i=0; i < 4; i++) {
	  	unsigned char a,b,c,d;
		a = base[dir+4*i+0];
  		b = base[dir+4*i+1];
	  	c = base[dir+4*i+2];
		d = base[dir+4*i+3];
		offset += sprintf(&linea[offset],"%02x %02x %02x %02x ", a, b, c, d);
	  }
      // Loop how many hex numbers to display.
	  for(int i=0; i < 16; i++) {
          // Check if character is printable.
		  if (isprint(base[dir+i])) {
			  offset += sprintf(&linea[offset], "%c", base[dir+i]);
		  }
		  else {
			  offset += sprintf(&linea[offset],".");
		  }
	  }
	  sprintf(&linea[offset],"\n");

  	return(strdup(linea));
}

int read_char() {
    int chars[5];
    int ch,i=0;
    nodelay(stdscr, TRUE);
    while((ch = getch()) == ERR); // Active wait.
    ungetch(ch);
    while((ch = getch()) != ERR) {
        chars[i++]=ch;
    }
    // Converts to number with everything read.
    int res=0;
    for(int j=0; j<i; j++) {
        res <<= 8;
        res |= chars[j];
    }

    return res;
}
