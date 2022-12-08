# Makefile for Threads vs Forks programs

.PHONY = all clean PRINT

CC = gcc
LINKERS = -lncurses

all:
	${CC} bubble_forks.c -o bubble_forks.exe
	${CC} bubble_threads.c -o bubble_threads.exe

clean:
	@echo "\nRemoving all binary and executable files...\n"
	@rm -rvf *.o
	@rm -rvf *.exe
	@echo "\n"
