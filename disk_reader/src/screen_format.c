#include "screen_format.h"

void print_mbr(mbr_register partitions[4], int *i, int u_in) {
    mvprintw(2, 5, "Name");
    mvprintw(2, 20, "LBA");
    mvprintw(2, 35, "Size");

    switch(u_in) {
        case KEY_UP:
            *i = (*i>0) ? *i - 1 : 3;
            break;
        case KEY_DOWN:
            *i = (*i<3) ? *i + 1 : 0;
            break;
        default:
            break; // Nothing 
    }

    for (int j=0; j < 4; j++) {
        char part_name[12], part_size[13], part_start[13];

        if (j == *i) attron(A_REVERSE);
         
        sprintf(part_name, "Partition %d", j);
        mvprintw(4+j, 5, part_name);
        if (partitions[j].size + partitions[j].lba == 0) {
            sprintf(part_size, "NaN");
            sprintf(part_start, "NaN");
        } else {
            sprintf(part_size, "%d bytes", partitions[j].size);
            sprintf(part_start, "%d", partitions[j].lba);
        }
        mvprintw(4+j, 20, part_start);
        mvprintw(4+j, 35, part_size);
         
        attroff(A_REVERSE);
    }
    move(4 + *i, 5);
    refresh();
}