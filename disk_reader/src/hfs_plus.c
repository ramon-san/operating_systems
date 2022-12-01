#include "hfs_plus.h"
#include "screen_format.h"

/**
 * Function to move to a partition based on an MBR register.
 * 
 * @param disk              Memory map of disk file.
 * @param partition_info    MBR register structure with partition info.
 * 
 * @return Number indicating where a partition starts.
 */
int move_to_partition(char *disk, mbr_register partition_info) {
    char hex_text[11] ;
    int block_size = 512, offset = 0x400; // Given by Apple documentation
    int hex_location = 0, partition_location = 0;

    partition_location = block_size * partition_info.lba;
    partition_location += offset;
    return partition_location;
}

/**
 * Function to get basic information from HFS Plus memory partition.
 * 
 * @param location  Number indicating were a partition starts.
 * 
 */
HFSPlusVolumeHeader hfs_plus_info(char *disk, int location) {
    HFSPlusVolumeHeader part_info;
    
    memcpy(&part_info, &disk[location], sizeof(part_info));
    
    return part_info;
}