#!/bin/sh

make clean -C src/
make -C src/
./src/hex_editor.exe test_file.dsk
