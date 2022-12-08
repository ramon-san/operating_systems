#include <stdio.h>
#include <dirent.h>

int main(int argc, char const *argv[]) {
    struct dirent *directoryContent;
    char *directoryName = (char *)argv[1];
    char file_type = '\0';
    if (directoryName == NULL) directoryName = "./";
    DIR  *directory = opendir(directoryName);
    while ((directoryContent = readdir(directory)) != NULL) {
	if (directoryContent->d_type == 4) {
	    file_type = 'd';
	} else if (directoryContent->d_type == 8) {
	    file_type = 'f';
	} else {
	    file_type = '?';
	}
        printf("%u (%c) - %s\n", directoryContent->d_reclen, file_type, directoryContent->d_name);
    }
    // printf("\n\nDirectory: %p\n\n", (directoryContent));
    closedir(directory);
}
