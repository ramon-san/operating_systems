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
	// Increase shared memory object, its cero by default.
	res = ftruncate(fd, buffer_size);
	if (res == -1) {
		perror("\n\tError in ftruncate()");
		exit(20);
	}

	return fd;
}

/**
 * Function write into a shared memory object.
 * 
 * @param name		  Name of the conversation to write into.
 * @param buffer_size Byte size assigned to the object.
 * @param fd		  File descriptor for object we're using.
 * 
 */
void type_in_shared_memory(char *name, int buffer_size, int fd) {
	void *addr;
	int len, res;
	char message[buffer_size];

	fflush(stdin); // Try to fix scanf() ignore problem.
	printf("\n\tMessage to %s: ", name);
	scanf(" %[^\n]", message);

	// Map process memory.
	addr = mmap(NULL, buffer_size, PROT_WRITE, MAP_SHARED, fd, 0);
	if (addr == MAP_FAILED) {
		perror("\n\tError in mmap()");
		exit(30);
	}

	// Add data to shared memory.
	len = strlen(message) + 1;
	memcpy(addr, message, buffer_size);

	// End mmap() function.
	res = munmap(addr, buffer_size);
	if (res == -1) {
		perror("\n\tError in munmap()");
		exit(40);
	}
}

/**
 * Function read from a shared memory object.
 * 
 * @param name		  Name of the conversation to read from.
 * @param buffer_size Byte size assigned to the object.
 * @param fd		  File descriptor for object we're using.
 * 
 */
void read_from_shared_memory(char *name, int buffer_size, int fd) {
	char message[buffer_size];
	void *addr;

	// Map memory process.
	addr = mmap(NULL, buffer_size, PROT_READ, MAP_SHARED, fd, 0);
	if (addr == MAP_FAILED) {
		perror("\n\tError in mmap()");
		exit(30);
	}

	// Save read message in memory.
	memcpy(message, addr, buffer_size);

	printf("\n\tLast message in %s: \"%s\"\n", name, message);
}

/**
 * Function to close shared memory object.
 * 
 * @param memory_name Name of the memory object to delete.
 *
 */
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