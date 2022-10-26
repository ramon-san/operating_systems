#!/bin/sh

make clean -C src/
make -C src/
./src/hex_editor.exe ./test_files/test_1k
stty sane
