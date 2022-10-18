# Hex editor

El archivo checkSum.c hace una suma sobre el archivo que se da como argumento. Es una suma simple de los bytes en el archivo.
Se compila con:
  gcc -o checkSum checkSum.c
  
El archivo hexEditor.c es el esqueleto para un editor hexadecimal de archivos. Se da el archivo a editar como argumento del programa.

Se compila con:
  gcc -o hexEditor hexEditor.c -lncurses

A quick implementation of an hexadecimal editor created with C.

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
./messenger.exe ${FILE}
```

Here the `${FILE}` parameter represents the file you want to open. The src files are spread all over the place to follow a modular architecture and follow what I currently consider best practices. When running the code from `run.sh` a file called `hex_editor/test_file.dsk` gets opened in the editor by default.

## Teacher instructions

Create an hexadecimal editor with capacity to...