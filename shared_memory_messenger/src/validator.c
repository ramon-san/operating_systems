#include "validator.h"

/**
 * Function to validate a new conversation can be created.
 *
 * @param msg_controller    Main structure to control all messages in program.
 *
 */
void validate_new_conv(message_board *msg_controller, int buffer_size) {
    char temp_name[12]; // Temporary name to create new conversation.
    int fd, position;

    if (msg_controller->open_convs >= 3) {
        print_color("red", "Maximum number of conversation reached.");
        return;
    }
    printf("\n\tContact name: ");
    scanf(" %s", temp_name);
    if (strlen(temp_name) > 12) {
        print_color("red", "Contact name must be less than 12 characters long.");
        return;
    }
    system("clear");
    pass_to_controller(msg_controller, temp_name, NULL);
    position = msg_controller->open_convs-1;
    fd = getSharedMemory(msg_controller->storage_ids[position], buffer_size);
    msg_controller->file_descriptors[position] = fd;

    green(); printf("\n\tOpening chat with: %s\n\n", temp_name); default_color();
}

/**
 * Function that passes data into the message_board object.
 * 
 * @param msg_controller    Main structure to control all messages in program.
 * @param name              Name of new person to add in structure.
 * @param position          Pass NULL if autoincrement, int address otherwise.
 * 
 */
void pass_to_controller(message_board *msg_controller, char* name, int *position) {
    if (position == NULL) {
        strcpy(msg_controller->conv_names[msg_controller->open_convs], name);
        strcpy(msg_controller->storage_ids[msg_controller->open_convs], "/");
        strcat(msg_controller->storage_ids[msg_controller->open_convs], name);
        msg_controller->open_convs++;
        msg_controller->total_convs++;
    } else {
        strcpy(msg_controller->conv_names[*position-1], name);
        strcpy(msg_controller->storage_ids[*position-1], "/");
        strcat(msg_controller->storage_ids[*position-1], name);
        msg_controller->open_convs--;
    }
}

/**
 * Function to change conversation between users.
 * 
 * @return Conversation number of conversation we're changing to.
 *
 */
int change_conv() {
    int change_to;
    printf("\n\tWho do you want to text: ");
    scanf(" %d", &change_to);
    if (change_to < 0 || change_to > 2) {
        print_color("red", "Number given is not valid, ID now set to 0.");
        return 0;
    }
    return change_to;
}

/**
 * Function that drops the last conversation from program message controller.
 *
 * @param msg_controller Main structure to control all messages in program.
 *  
 * @return ID of origin to avoid mistakes.
 * 
 */
int drop_conversation(message_board *msg_controller) {
    close_shared_memory(msg_controller->storage_ids[msg_controller->open_convs]);
    pass_to_controller(msg_controller, "trash", &msg_controller->open_convs);
    red();
    printf("\n\tLast conversation from list dropped.\n");
    default_color();
    return 0;
}