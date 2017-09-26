// Adjust the `bytes` variable to match the required amount of memory
// Compile with: gcc -Wall -Wextra -lrt shared_mem.c -o shared_mem
// Then execute with ./shared_mem
//

#include <sys/types.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>



#define PRESS_ENTER printf("press enter\n"); getchar();


size_t bytes = 10 * 1024 * 1024;  // 10 MiB = 5 huge pages
char* shared_mem;  // pointer to shared memory



void alloc_shared_memory_with_shm_open(void) {
	printf("Testing shared memory allocation using shm_open (/dev/shm)\n");

	char shared_name[] = "/my_shm";
	int fd = shm_open(shared_name, O_RDWR|O_CREAT, S_IRUSR|S_IWUSR);
	if (fd < 0) {
		printf("Unable to open shared memory %d\n", errno);
		return;
	}
	if (ftruncate(fd, bytes) != 0) {
		printf("Unable to truncate memory %d\n", errno);
		return;
	}

	printf("Allocating %zu bytes of shared memory... ", bytes);
	shared_mem = mmap(NULL, bytes, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	if (shared_mem == MAP_FAILED) {
		printf("Unable to allocate %zu bytes\n", bytes);
		return;
	}
	printf("OK\n");

	PRESS_ENTER

	printf("Writing to shared memory... ");
	for (size_t i=0; i < bytes; i++) {
		shared_mem[i] = 1;
	}
	printf("OK\n");

	PRESS_ENTER
	printf("Freeing memory... ");
	if (munmap(shared_mem, bytes) != 0) {
		printf("munmap failed\n");
	}
	else {
		printf("OK\n");
	}
	printf("OK\n");
	PRESS_ENTER

	printf("Closing file descriptor...");
	if (shm_unlink(shared_name) != 0) {
		printf("Unable to close fd\n");
	}
	PRESS_ENTER
}


void alloc_shared_memory(void) {
	printf("Testing shared memory allocation using MAP_ANONYMOUS\n");

	printf("Allocating %zu bytes of shared memory using mmap... ", bytes);
	shared_mem = mmap(NULL, bytes, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
	if (shared_mem == MAP_FAILED) {
		printf("Unable to allocate %zu bytes\n", bytes);
		return;
	}
	printf("OK\n");

	PRESS_ENTER

	printf("Writing to shared memory... ");
	for (size_t i=0; i < bytes; i++) {
		shared_mem[i] = 1;
	}
	printf("OK\n");

	PRESS_ENTER
	printf("Freeing memory... ");
	if (munmap(shared_mem, bytes) != 0) {
		printf("munmap failed\n");
	}
	else {
		printf("OK\n");
	}

	PRESS_ENTER
}


void alloc_huge_pages(void) {
	printf("Testing huge pages shared memory\n");

	printf("Allocating %zu bytes of huge pages... ", bytes);
	shared_mem = mmap(NULL, bytes, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS|MAP_HUGETLB, -1, 0);
	if (shared_mem == MAP_FAILED) {
		printf("Unable to allocate %zu bytes (check /proc/sys/vm/nr_hugepages)\n", bytes);
		return;
	}
	printf("OK\n");

	PRESS_ENTER

	printf("Writing to huge pages... ");
	for (size_t i=0; i < bytes; i++) {
		shared_mem[i] = 1;
	}
	printf("OK\n");

	PRESS_ENTER

	printf("Freeing huge pages... ");
	if(munmap(shared_mem, bytes) != 0) {
		printf("munmap failed\n");
	}
	else {
		printf("OK\n");
	}
	PRESS_ENTER
}


int main(void) {
	alloc_shared_memory();
	alloc_shared_memory_with_shm_open();
	alloc_huge_pages();
}
