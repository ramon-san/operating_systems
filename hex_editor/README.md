# Hex editor

A quick implementation of an hexadecimal editor created with C. This repo contains test files with different byte sizes on the `hex_editor/test_files/` directory, the byte size of this file appears on their name. For example, `test_1k` indicates this file has 1,000 bytes, to create files of any given size in MacOS run the following command:

``` Shell
dd if=/dev/zero of=new_file_name bs=100 count=1
```

The block size (`bs`) you indicate in the previous command indicates the size of your new file. By assigning the input file (`if`) called `/dev/zero` we indicate that all bytes on our new file should be zero. 

## Run the code

### Short way

Simply run `./run.sh` on the `hex_editor/` directory.

### Long way

To compile the code you just need to run the following command inside the `hex_editor/src/` directory:

``` Shell
make
```

Once you have the executable version run it with:

``` Shell
./hex_editor.exe ${FILE}
```

Here the `${FILE}` parameter represents the file you want to open. The src files are spread all over the place to follow a modular architecture and follow what I currently consider best practices. When running the code from `run.sh` a file called `hex_editor/example` gets opened in the editor by default.

> If the hex editor breaks your terminal, run: `stty sane`. This command is automatically used if you execute the `run.sh` script.

## Teacher instructions

Create an hexadecimal editor that allows changes the memory of file being edited.
