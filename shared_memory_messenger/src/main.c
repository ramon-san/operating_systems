#include "structures.h"
#include "styles.h"
#include "validator.h"
#include "shared_memory.h"

int main(int argc, char *argv[]) {
    int buffer_size = atoi(argv[1]);
    char input;
    int location = 0; // Menu page is 0 and messenger is 1.
    int current_conv = 0;
    message_board msg_controller; // Init message_board object (struct).
    msg_controller.total_convs = 0;
    msg_controller.open_convs = 0;
    system("clear");

    if (buffer_size > 256) {
        print_color("red", "Buffer size is to big, please use under 256 Bytes.");
        return 0;
    }

    while (1) {
        if (location == 0) {
            input = print_menu();

            // Control user option menu with switch statement.
            switch (input) {
                case 'E':
                    print_message_board_history(msg_controller);
                    green(); printf("\n\tBye!\n\n"); default_color();
                    return 0;
                case 'S':
                    validate_new_conv(&msg_controller, buffer_size);
                    break;
                case 'D':
                    print_convs(msg_controller);
                    current_conv = drop_conversation(&msg_controller);
                    break;
                case 'P':
                    print_convs(msg_controller);
                    break;
                case 'G':
                    system("clear");
                    print_id_data(msg_controller, current_conv);
                    break;
                case 'C':
                    print_convs(msg_controller);
                    current_conv = change_conv();
                    print_id_data(msg_controller, current_conv);
                    break;
                case 'T':
                    type_in_shared_memory(msg_controller.storage_ids[current_conv], buffer_size, msg_controller.file_descriptors[current_conv]);
                    break;
                case 'R':
                    printf("\n\tMissing [R]ead implementation.\n\n");
                    break;
                default:
                    print_color("red", "Please enter a valid option.");
                    break;
            }
        }
    }
}