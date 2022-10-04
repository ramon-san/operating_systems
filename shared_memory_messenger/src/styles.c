#include "styles.h"

/**
 * Function that prints menu and receives a user input.
 * 
 * @return Character with user input value.
 *
 */
char print_menu() {
    char input;
    printf("\nWhat do you want to do:\n\n\
    [S]tart conversation\n\
    [D]rop conversation\n\
    [C]hange conversations\n\
    [P]rint conversations\n\
    [G]et current conversation\n\
    [T]ext current conversation\n\
    [R]ead current conversation\n\
    [E]xit\n\n\tInput: ");
    scanf(" %c", &input);
    return toupper(input); // Save input as upper case value.
}

/**
 * Function to print statement with specified color.
 * 
 * @param color     Color to print in, valid: "red", "green" and "blue".
 * @param to_print  Text to print.
 *  
 */
void print_color(char *color, char *to_print) { 
    system("clear");
    // Select given color for print.
    if (strcmp("red", color) == 0) printf("\033[1;31m");
    else if (strcmp("green", color) == 0) printf("\033[0;32m");
    else if (strcmp("blue", color) == 0) printf("\033[0;34m");
    // Print given statement.
    printf("\n\t%s\n\n", to_print); 
    // Return to default color.
    printf("\033[0m");
}

/**
 * Function to change text to green.
 *
 */
void green() { printf("\033[0;32m"); }

/**
 * Function to change text to red.
 *
 */
void red() { printf("\033[1;31m"); }

/**
 * Function to change text to default color.
 *
 */
void default_color() { printf("\033[0m"); }