#include "interface.h"

int main(int argc, char const *argv[]) {
	initscr();			

    /* El archivo se da como parametro */
    if (argc != 2) {
        printf("Se usa %s <archivo> \n", argv[0]);
        return(-1);
    }

    edit((char *)argv[1]);

    endwin();
    
    return 0;
}