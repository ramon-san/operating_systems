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
	void *addr;
	char data[buffer_size];

	// Get shared memory object (this is not a file).
	fd = shm_open("/probando", O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);
	if (fd == -1) {
		perror("\n\tError in shm_open()");
		exit(10);
	}
	printf("File descriptor: %d and buffer: %d", fd, buffer_size);
	// Increase shared memory object, its cero by default.
	res = ftruncate(fd, buffer_size);
	if (res == -1) {
		perror("\n\tError in ftruncate()");
		exit(20);
	}

	return fd;
}

void type_in_shared_memory(char *memory_name, int buffer_size, int fd) {
	int addr, len, res;
	char *message;

	scanf(" %s", message);

	printf("received message %s", message);
	// // Map process memory.
	// addr = mmap(NULL, buffer_size, PROT_WRITE, MAP_SHARED, fd, 0);
	// if (addr == MAP_FAILED) {
	// 	perror("mmap");
	// 	return 30;
	// }

	// // Add data to shared memory.
	// len = strlen(message) + 1;
	// memcpy(addr, message, buffer_size);

	// // End mmap() function.
	// res = munmap(addr, buffer_size);
	// if (res == -1) {
	// 	print_color("red", "Error using function munmap().");
	// 	return 40;
	// }
}

void close_shared_memory(char *memory_name) {
	printf("Attempting to close %s", memory_name);
	int fd = shm_unlink(memory_name);
	if (fd == -1) {
		perror("\n\tError in shm_unlink()");
		exit(100);
	}
	green();
	printf("\n\tShared memory for %s close successfully.\n", memory_name);
	default_color();
}