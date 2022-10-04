#ifndef validator_h
#define validator_h

// Basic C libraries.
#include <stdio.h>
#include <string.h>

// Personal libraries.
#include "structures.h"
#include "styles.h"

void validate_new_conv(message_board *msg_controller);
/**
 * Function to validate a new conversation can be created.
 *
 * @param msg_controller Main structure to control all messages in program.
 *
 */

void pass_to_controller(message_board *msg_controller, char* name);
/**
 * Function that passes data into the message_board object.
 * 
 * @param msg_controller Main structure to control all messages in program.
 * @param name Name of new person to add in structure.
 * 
 */

 int change_conv();
/**
 * Function to change conversation between users.
 * 
 * @return Conversation number of conversation we're changing to.
 *
 */

void drop_conversation(message_board *msg_controller);
/**
 * Function that drops a given conversation and frees the memory object.
 *
 * @param msg_controller Main structure to control all messages in program.
 *  
 */
 
#endif