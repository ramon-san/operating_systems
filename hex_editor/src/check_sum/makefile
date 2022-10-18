# makefile for hex_editor.exe

.PHONY = all clean PRINT

CC = gcc
# LINKERS = -lncurses
# FLAGS = -C0

deps = $(wildcard *.c)
BINS = $(deps:%.c=%.o)

all: ${BINS} check_sum.exe

${BINS}: ${deps}
	@echo "\nGenerating binary objects."
	${CC} -c $^

check_sum.exe: ${BINS}
	@echo "\nGenerating executable."
	${CC} $^ -o $@ ${LINKERS}
	@echo "\n"

clean:
	@echo "\nRemoving all binary and executable files...\n"
	@rm -rvf *.o
	@rm -rvf *.exe
	@echo "\n"
