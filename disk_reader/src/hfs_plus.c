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

/**
 * Function to move to the partition's catalog file.
 * 
 * @param block_size    Volume header content for blockSize.
 * @param start_block   Volume header content for catalog file startBlock.
 * @param start         Location where partition was initialized.
 * 
 * @return Integer with file location.
 */
int move_to_catalog_file(UInt32 block_size, UInt32 start_block, int start) {
    int location, offset = 0x400; // Offset was given by Apple documentation.

    location = block_size*start_block+start-offset;

    return location;
}

HFSPlusForkData catalog_file_info (char *disk, int location) {
    HFSPlusForkData cf_info;

    memcpy(&cf_info, &disk[location], sizeof(cf_info));
    
    return cf_info;
}

/**
 * Function to get info from HFS Plus node descriptor.
 * 
 * @param location  Number indicating were a partition starts.
 * 
 * @return Node descriptor with catalog file information.
 */
BTNodeDescriptor node_descriptor_info(char *disk, int location) {
    BTNodeDescriptor nd_info;

    memcpy(&nd_info, &disk[location], sizeof(nd_info));

    return nd_info;
}

