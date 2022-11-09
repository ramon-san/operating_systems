# makefile for hex_editor.exe

.PHONY = all clean PRINT

CC = gcc
LINKERS = -lncurses
#CFLAGS = -C0

deps = $(wildcard *.c)
BINS = $(deps:%.c=%.o)

all: ${BINS} hex_editor.exe

${BINS}: ${deps}
	@echo "\nGenerating binary objects."
	${CC} ${CFLAGS} -c $^ 

hex_editor.exe: ${BINS}
	@echo "\nGenerating executable."
	${CC} ${LDFLAGS} $^ -o $@ ${LINKERS}
	@echo "\n"

clean:
	@echo "\nRemoving all binary and executable files...\n"
	@rm -rvf *.o
	@rm -rvf *.exe
	@echo "\n"
