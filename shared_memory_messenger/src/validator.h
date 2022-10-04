#ifndef validator_h
#define validator_h

// Basic C libraries.
#include <stdio.h>
#include <string.h>

// Personal libraries.
#include "shared_memory.h"
#include "structures.h"
#include "styles.h"

void validate_new_conv(message_board *msg_controller, int buffer_size);
/**
 * Function to validate a new conversation can be created.
 *
 * @param msg_controller Main structure to control all messages in program.
 * @param max_conv_number   Maximum number of conversation to process.
 *
 */

void pass_to_controller(message_board *msg_controller, char* name, int *position);
/**
 * Function that passes data into the message_board object.
 * 
 * @param msg_controller    Main structure to control all messages in program.
 * @param name              Name of new person to add in structure.
 * @param position          Pass NULL if autoincrement, int address otherwise.
 * 
 */

 int change_conv();
/**
 * Function to change conversation between users.
 * 
 * @return Conversation number of conversation we're changing to.
 *
 */

int drop_conversation(message_board *msg_controller);
/**
 * Function that drops a given conversation and frees the memory object.
 *
 * @param msg_controller Main structure to control all messages in program.
 *  
 * @return ID of origin to avoid mistakes.
 * 
 */
 
#endif