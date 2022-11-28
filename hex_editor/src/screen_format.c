#include "screen_format.h"

/**
* Function to print editor screen.
*
* @param map    Memory address of file we're editing.
* @param offset Position where we should start printing.
* @param fr     File size of what we're editing.
*
*/
void print_screen(char *map, int *offset, long fr, int *y_axis, int *x_axis, char *filename) {
    char status_text[100];

	// Check overflow logic to limit things for given file size.
    if (fr <= 25) {
		if (*offset == -1) *y_axis = 24;
		if (*offset == 1) *y_axis = 0;
		*offset = 0;
	} else {
		if (*offset == -1) {
			*offset = fr-25;
			*y_axis = 24;
		} else if (fr-24 == *offset && *y_axis == 24) {
			*y_axis = 0;
			*offset = 0;
		}
	}
	
    // Create lines for editor screen.
    for(int i=0; i<25; i++) {
        // Create line, base, and offset.
        char *l = make_line(map, *offset*16+i*16);
        move(i, 0);
		addstr(l); // values are y-axis, x-axis, and content.
    }
    sprintf(status_text, "Located in y = %i and x = %i (%i).", *y_axis, *x_axis, *offset);
    move(26, 0);
	clrtoeol();
	mvprintw(26, 0, status_text);
	sprintf(status_text, "Map address: %p", map);
	mvprintw(28, 0, status_text);
	mvprintw(30, 0, "Move to: ");
    attron(A_STANDOUT | A_UNDERLINE);
    mvprintw(32, 0, filename);
    attroff(A_STANDOUT | A_UNDERLINE);
	mvprintw(34, 0, "[TAB]: search | [ESC]: exit");
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
