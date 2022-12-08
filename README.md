# Operating Systems

Programs made for the Operating Systems course I took with [Dr. René Mac Kinney Romero](https://github.com/rene-mkr) at Universidad Iberoamericana. This repo contains some low-level C programs that help you manage different things in an operating system; while taking this course my operating system was **MacOS Ventura Version 13.0.1**, but most things should work on Linux machines as well.

> Some projects have Docker containers to provide a stable running environment.

## What projects are there?
Inside this repository you'll find a couple of interesting projects which I think are awesome!

### [System Utils](./system_utils/)
These are three simple programs that recreates basic system utilities for MacOS.

### [Threads VS Forks](./threads_vs_forks/)
These are two programs let's you compare the speed between running a sorting algorithm with threads and running this same algorithm with forks.

### [Shared Memory Messenger](./shared_memory_messenger/)
This program allows you to simulate a messenger through the use of a shared memory objects. In Linux machines this objects are found in the `/dev/shmem` directory, but in MacOS no such file exists. 

> To understand how shared memory is managed in MacOS read through the manual entry for `shm_open`, there they state: "There is no visible entry in the file system for the created object in this implementation."

### [Hex Editor](./hex_editor/)
This program is an hexadecimal editor, you can use it to open any file.

### [Disk Reader](./disk_reader/)
This is a program that reads an HFS+ disk image and gives you information about its structure.

## How to run this things?
Instructions for running each program can be found in the README.md file of each project.


