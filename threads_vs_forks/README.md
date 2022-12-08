# Forks vs Threads

This is a simple program that does a bubble sort and is followed by an inefficient merge sort. There are two files and they both use your CPU in a different manner, one uses process forks to fullfil your request and the other one uses threads.

When using threads please consider that the resulting time should be multiplied by two to get an approximation of what both processes took. This is a vague approximation, but it works as an estimate.

## Running the code

To get the executable files for all of this directories use `make` command. To delete binary files and executables use `make clean`. 

You have to run each code separately and to control the amount of data that they'll loop you have to edit the `ARRAY_SIZE` global variable that you'll see in each file. You can also control the range of random numbers to be generated with the `RANDOM_SIZE` global variable.