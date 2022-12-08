# Systems Utils

This repo contains three simple imitations of what could be considered to be system utils on MacOS. The three utilities created are the following:

- `list_dirs` this is a simple piece of code that simulates in a very basic way what the `ls` command does in Linux. You can control the directory in which you want to read by giving a parameter to the program's execution.
- `process_time` this program tells you how long the computer takes to iterate on a given for loop. You can control the size of this loop by giving a parameter to the program's execution.
- `system_info` this gives basic information about the system that's running the program (system name, release, machine name, et cetera).

## Running the code

To get the executable files for all of this directories use `make` command. To delete binary files and executables use `make clean`. After this you can run the executables as follows:

- `./list_dirs.exe` This will list your current directory, you can pass another directory as a parameter.
- `./process_time` This will give you the time it takes to loop 10,000,000 times inside of a for statement, but you can change this number by passing another positive integer as a parameter.
- `system_info` This will give you basic information of your system and doesn't take on any parameters.