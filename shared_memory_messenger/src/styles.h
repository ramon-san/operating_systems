#ifndef styles_h
#define styles_h

// Basic C libraries.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char print_menu();
/**
 * Function that prints menu and receives a user input.
 * 
 * @return Character with user input value.
 *
 */
 
void print_color(char *color, char *to_print);
/**
 * Function to print statement with specified color.
 * 
 * @param color     Color to print in, valid: "red", "green" and "blue".
 * @param to_print  Text to print.
 *  
 */
 
void green();
/**
 * Function to change text to green.
 *
 */

void red();
/**
 * Function to change text to red.
 *
 */

void default_color();
/**
 * Function to change text to default color.
 *
 */

#endif