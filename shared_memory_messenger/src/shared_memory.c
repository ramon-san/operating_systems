#include "shared_memory.h"

/**
 * Function that creates a shared memory object.
 * 
 * @param memory_name Name of the memory object to create.
 * @param buffer_size Byte size assigned to the object.
 * 
 */
int getSharedMemory(char *memory_name, int buffer_size) {
	int res, len, fd; // fd = file descriptor.
	char data[buffer_size];

	// Get shared memory object (this is not a file).
	fd = shm_open(memory_name, O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);
	if (fd == -1) {
		perror("\n\tError in shm_open()");
		exit(10);
	}
	//printf("\n\tFile descriptor: %d and buffer: %d\n", fd, buffer_size);
	// Increase shared memory object, its cero by default.
	res = ftruncate(fd, buffer_size);
	if (res == -1) {
		perror("\n\tError in ftruncate()");
		exit(20);
	}

	return fd;
}

void type_in_shared_memory(char *memory_name, int buffer_size, int fd) {
	void *addr;
	int len, res;
	char message[buffer_size];

	fflush(stdin); // Try to fix scanf() ignore problem.
	printf("Message: ");
	scanf(" %[^\n]", message);

	// // Map process memory.
	// addr = mmap(NULL, buffer_size, PROT_WRITE, MAP_SHARED, fd, 0);
	// if (addr == MAP_FAILED) {
	// 	perror("\n\tError in mmap()");
	// 	exit(30);
	// }

	// // Add data to shared memory.
	// len = strlen(message) + 1;
	// memcpy(addr, message, buffer_size);

	// // End mmap() function.
	// res = munmap(addr, buffer_size);
	// if (res == -1) {
	// 	perror("\n\tError in munmap()");
	// 	exit(40);
	// }
}

void close_shared_memory(char *memory_name) {
	int fd = shm_unlink(memory_name);
	if (fd == -1) {
		perror("\n\tError in shm_unlink()");
		exit(100);
	}
	green();
	printf("\n\tShared memory for %s close successfully.\n", memory_name);
	default_color();
}