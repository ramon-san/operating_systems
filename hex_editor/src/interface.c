#include "interface.h"

char *make_line(char *base, int dir) {
	  char linea[100]; // La linea es mas pequeña
	  int o=0;
	  // Muestra 16 caracteres por cada linea
	  o += sprintf(linea,"%08x ",dir); // offset en hexadecimal
	  for(int i=0; i < 4; i++) {
	  	unsigned char a,b,c,d;
		a = base[dir+4*i+0];
  		b = base[dir+4*i+1];
	  	c = base[dir+4*i+2];
		d = base[dir+4*i+3];
		o += sprintf(&linea[o],"%02x %02x %02x %02x ", a, b, c, d);
	  }
	  for(int i=0; i < 16; i++) {
		  if (isprint(base[dir+i])) {
			  o += sprintf(&linea[o],"%c",base[dir+i]);
		  }
		  else {
			  o += sprintf(&linea[o],".");
		  }
	  }
	  sprintf(&linea[o],"\n");

  	return(strdup(linea));
}

char *map_file(char *filePath, int *fd) {
    /* Abre archivo */
    *fd = open(filePath, O_RDONLY);
    if (*fd == -1) {
    	perror("Error abriendo el archivo");
	    return(NULL);
    }

    /* Mapea archivo */
    struct stat st;
    fstat(*fd,&st);
    int fs = st.st_size;

    char *map = mmap(0, fs, PROT_READ, MAP_SHARED, *fd, 0);
    if (map == MAP_FAILED) {
    	close(*fd);
	    perror("Error mapeando el archivo");
	    return(NULL);
    }

    return map;
}

int read_char() {
    int chars[5];
    int ch,i=0;
    nodelay(stdscr, TRUE);
    while((ch = getch()) == ERR); /* Espera activa */
    ungetch(ch);
    while((ch = getch()) != ERR) {
        chars[i++]=ch;
    }
    /* convierte a numero con todo lo leido */
    int res=0;
    for(int j=0;j<i;j++) {
        res <<=8;
        res |= chars[j];
    }
    return res;
}


int edit(char *filename) {
    int fd; // Archivo a leer

    /* Lee archivo */
    char *map = map_file(filename, &fd);
    if (map == NULL) {
        exit(EXIT_FAILURE);
    }
    
    for(int i= 0; i<25; i++) {
      	// Haz linea, base y offset
    	  char *l = make_line(map,i*16);
	      mvprintw(i,0,l);
    }
    refresh();

    read_char();

    if (munmap(map, fd) == -1) {
        perror("Error al desmapear");
    }
    close(fd);
    
    return 0;

}
