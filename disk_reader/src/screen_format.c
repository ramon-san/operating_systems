#include "screen_format.h"

/**
 * Function to print MBR information to user and navigate as menu.
 * 
 * @param partitions    Array with MBR registers.
 * @param i             Index for curser.
 * @param u_in          Input from user.
 * 
 */
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

/**
 * Function to print basic HFS+ info.
 * 
 * @param info  Structure for HFS+ Volume Header.
 * 
 */
void print_volume_header(HFSPlusVolumeHeader info) {
    char sig[3], sig_text[16];
    char ver_text[30], file_cnt_text[30], folder_cnt_text[30];
    
    info.signature = BIG_ENDIAN_16(info.signature);
    info.version = BIG_ENDIAN_16(info.version);
    info.folderCount = BIG_ENDIAN_32(info.folderCount);
    info.fileCount = BIG_ENDIAN_32(info.fileCount);

    string_uint16(sig, info.signature);

    sprintf(sig_text, "- Signature: %2s", sig);
    sprintf(ver_text, "- Version: %d", info.version);
    sprintf(file_cnt_text, "- File count: %d", info.fileCount);
    sprintf(folder_cnt_text, "- Folder count: %d", info.folderCount);

    mvprintw(2, 5, "Basic disk information:");
    mvprintw(4, 5, sig_text);
    mvprintw(5, 5, ver_text);
    mvprintw(6, 5, file_cnt_text);
    mvprintw(7, 5, folder_cnt_text);
    mvprintw(9, 5, "Press [ENTER] to continue...");

    return;
}

/**
 * Function to print disk catalog file.
 * 
 * @param info      Header record with catalog file information.
 * @param location  Memory address where this structure starts.
 * 
 */
void print_catalog_file(BTHeaderRec info, int location) {
    char ls_text[30], cs_text[30], root_node[30], total_nodes[30];
    char first_node[30], last_node[30], catalog_location[40];
    
    info.rootNode = BIG_ENDIAN_32(info.rootNode);
    info.nodeSize = BIG_ENDIAN_16(info.nodeSize);
    info.clumpSize = BIG_ENDIAN_32(info.clumpSize);
    info.totalNodes = BIG_ENDIAN_32(info.totalNodes);
    info.firstLeafNode = BIG_ENDIAN_32(info.firstLeafNode);
    info.lastLeafNode = BIG_ENDIAN_32(info.lastLeafNode);

    sprintf(catalog_location, "- Catalog file start: %x", location);
    sprintf(root_node, "- Root node: %x", info.rootNode);
    sprintf(ls_text, "- Node size: %x", info.nodeSize);
    sprintf(cs_text, "- Clump size: %x", info.clumpSize);
    sprintf(total_nodes, "- Total nodes: %x", info.totalNodes);
    sprintf(first_node, "- First leaf node: %x", info.firstLeafNode);
    sprintf(last_node, "- Last leaf node: %x", info.lastLeafNode);
    
    mvprintw(2, 5, catalog_location);
    mvprintw(4, 5, "Basic disk information:");
    mvprintw(6, 5, root_node);
    mvprintw(7, 5, first_node);
    mvprintw(8, 5, last_node);
    mvprintw(9, 5, ls_text);
    mvprintw(10, 5, cs_text);
    mvprintw(11, 5, total_nodes);
    mvprintw(13, 5, "Press [ENTER] to continue...");

    return;
}

/**
 * Function to print first leaf node.
 * 
 * @param info      Node descriptor with root node information.
 * @param location  Memory address where this structure starts.
 * 
 */
void print_first_leaf(BTNodeDescriptor info) {
    char records_text[30], fl_text[30], bl_text[30];
    
    info.numRecords = BIG_ENDIAN_16(info.numRecords);
    info.bLink = BIG_ENDIAN_32(info.bLink);
    info.fLink = BIG_ENDIAN_32(info.fLink);

    sprintf(records_text, "- Number of records: %x", info.numRecords);
    sprintf(fl_text, "- Forward link: %x", info.fLink);
    sprintf(bl_text, "- Backward link: %x", info.bLink);

    mvprintw(2, 5, "Root node descriptor:");
    mvprintw(4, 5, records_text);
    mvprintw(5, 5, fl_text);
    mvprintw(6, 5, bl_text);

    return;
}

// /**
//  * Function to print disk catalog file.
//  * 
//  * @param info  Node Descriptor with catalog file information.
//  * 
//  */
// void print_catalog_file(BTNodeDescriptor info) {
//     char flink_text[30], blink_text[30];
    
//     info.fLink = BIG_ENDIAN_16(info.fLink);
//     info.bLink = BIG_ENDIAN_16(info.bLink);

//     sprintf(flink_text, "- Fwd link: %d", info.fLink);
//     sprintf(blink_text, "- Bwd link: %d", info.bLink);
    
//     mvprintw(2, 5, "Basic disk information:");
//     mvprintw(4, 5, flink_text);
//     mvprintw(5, 5, blink_text);
//     mvprintw(7, 5, "Press [ENTER] to continue...");

//     return;
// }

/**
 * Function to change screen number and clear screen.
 * 
 * @param screen    Memory address of screen varaible.
 * @param number    Number of screen to change to.
 * @param u_in      User input memory address.
 * 
 */
void change_screen(int *screen, int number, int *u_in) {
    *screen = number;
    *u_in = 0;
    clear();
}

/**
 * Function tu use in debug, prints int in given line as location.
 * 
 * @param location  Row in screen where we'll print.
 * @param to_print  Integer value we want to print.
 * 
 */
void print_int(int location, int to_print) {
    char text[15];

    sprintf(text, "%d", to_print);
    mvprintw(location, 5, text);
}

/**
 * Function tu use in debug, prints int in given line as location.
 * 
 * @param location  Row in screen where we'll print.
 * @param to_print  Hex value we want to print.
 * 
 */
void print_hex(int location, int to_print) {
    char text[15];

    sprintf(text, "%x", to_print);
    mvprintw(location, 5, text);
}

/**
 * Function to pass UInt16 content to string.
 * 
 * @param text  Memory where text will be set.
 * @param value Integer value to set as text.
 * 
 */
void string_uint16(char *text, UInt16 value) {
    text[0] = value >> 8;
    text[1] = value & 0xff;
    text[2] = 0;
}

// /**
//  * Function to pass UInt32 content to string.
//  * 
//  * @param text  Memory where text will be set.
//  * @param value Integer value to set as text.
//  * 
//  */
// void string_uint32(char *text, UInt32 value) {
//     text[0] = value >> 8;
//     text[1] = value >> 16;
//     text[2] = value >> 24;
//     text[3] = value & 0xff;
//     text[4] = 0;
// }