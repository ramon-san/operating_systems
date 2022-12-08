# Makefile for System Utils programs

.PHONY = all clean PRINT

CC = gcc
LINKERS = -lncurses

all:
	${CC} list_dirs.c -o list_dirs.exe
	${CC} process_time.c -o process_time.exe
	${CC} system_info.c -o system_info.exe

clean:
	@echo "\nRemoving all binary and executable files...\n"
	@rm -rvf *.o
	@rm -rvf *.exe
	@echo "\n"
