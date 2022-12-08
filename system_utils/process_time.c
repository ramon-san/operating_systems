#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SLEEP 250000 // 1 second = 1000000 microseconds

void checkProcessingTime();

int main() {
    checkProcessingTime();
}

void checkProcessingTime(int argc, char const *argv[]) {
    int loop;

    if (argv[1] == NULL) loop = 10000000;
    else loop = atoi(argv[1]);

    if (loop <= 0) {
        printf("\nPlease enter a positive integer as a parameter.\n\n");
    } else {
        printf("\nLooping %i times.", loop);
        clock_t begin = clock();
        for (int i = 0; i < loop; i++); // Process to check processing time.
        clock_t end = clock();
        double timeSpent = (double)(end - begin) / CLOCKS_PER_SEC; // Pass result to seconds.
        printf("\nProcess took: %f seconds\n\n", timeSpent);
    }
}
