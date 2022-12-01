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
}

void print_volume_header(HFSPlusVolumeHeader info) {
    char sig[3], sig_text[16];
    char ver_text[100];
    
    info.signature = BIG_ENDIAN_16(info.signature);
    info.version = BIG_ENDIAN_16(info.version);
    sig[0] = info.signature >> 8;
    sig[1] = info.signature & 0xff;
    sig[2] = 0;
    sprintf(sig_text, "- Signature: %2s", sig);
    sprintf(ver_text, "- Version: %d", info.version);

    mvprintw(2, 5, "Basic disk information:");
    mvprintw(4, 5, sig_text);
    mvprintw(5, 5, ver_text);
}

void print_int(int location, int to_print) {
    char text[15];

    sprintf(text, "%d", to_print);
    mvprintw(location, 5, text);
}
