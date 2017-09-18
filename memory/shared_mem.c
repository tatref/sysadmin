// gcc -lrt shared_mem.c -o shared_mem
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


size_t bytes = 1024 * 1024 * 1024;
char* shared_mem;



void alloc_shared_memory_with_shm_open(void) {
	int fd = shm_open("my shared mem", O_RDWR|O_CREAT, S_IRUSR|S_IWUSR);
	if (fd < 0) {
		printf("Unable to open shared memory %d\n", errno);
		return;
	}
	if (ftruncate(fd, bytes) != 0) {
		printf("Unable to truncate memory %d\n", errno);
		return;
	}

	printf("Allocating %d bytes of shared memory... ", bytes);
	shared_mem = mmap(NULL, bytes, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	//shared_mem = mmap(NULL, bytes, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
	if (shared_mem == MAP_FAILED) {
		printf("Unable to allocate %d bytes\n", bytes);
		return;
	}
	printf("OK\n");

	PRESS_ENTER

	printf("Writing to shared memory... ");
	for (int i=0; i < bytes; i++) {
		shared_mem[i] = 1;
	}
	printf("OK\n");

	PRESS_ENTER
	printf("Freeing memory... ");
	munmap(shared_mem, bytes);
	printf("OK\n");
	PRESS_ENTER

	printf("Closing file descriptor...");
	if (shm_unlink("my shared mem") != 0) {
		printf("Unable to close fd");
	}
	PRESS_ENTER
}


void alloc_shared_memory(void) {
	printf("Allocating %d bytes of shared memory... ", bytes);
	shared_mem = mmap(NULL, bytes, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
	if (shared_mem == MAP_FAILED) {
		printf("Unable to allocate %d bytes\n", bytes);
		return;
	}
	printf("OK\n");

	PRESS_ENTER

	printf("Writing to shared memory... ");
	for (int i=0; i < bytes; i++) {
		shared_mem[i] = 1;
	}
	printf("OK\n");

	PRESS_ENTER
	printf("Freeing memory... ");
	munmap(shared_mem, bytes);
	printf("OK\n");
	PRESS_ENTER

	printf("Closing file descriptor...");
	if (shm_unlink("my shared mem") != 0) {
		printf("Unable to close fd");
	}
	PRESS_ENTER
}


void alloc_huge_pages(void) {
	printf("Allocating %d bytes of huge pages... ", bytes);
	shared_mem = mmap(NULL, bytes, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS|MAP_HUGETLB, -1, 0);
	if (shared_mem == MAP_FAILED) {
		printf("Unable to allocate %d bytes\n", bytes);
		return;
	}
	printf("OK\n");

	PRESS_ENTER

	printf("Writing to huge pages... ");
	for (int i=0; i < bytes; i++) {
		shared_mem[i] = 1;
	}
	printf("OK\n");

	PRESS_ENTER
	printf("Freeing huge pages... ");
	munmap(shared_mem, bytes);
	printf("OK\n");
	PRESS_ENTER
}


int main(void) {
	alloc_shared_memory();

	alloc_huge_pages();
}
