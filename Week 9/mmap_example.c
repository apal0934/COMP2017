#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#define SOME_DATA (24)

int  main(int argc, char** argv) {
	if (argc != 2) {
		// Need two arguments
		return 1;
	}

	char* block = NULL;
	int fd = open(argv[1], "w");
	struct stat stat_b;
	fstat(fd, &stat_b);
	block = mmap(NULL, stat_b.st_size, PROT_WRITE|PROT_READ,
			MAP_PRIVATE, fd, 0);
	if (block == MAP_FAILED) {
		perror("MMAP Failed");
		close(fd);
		return 1;
	}

	// read some bytes
	for (size_t i = 0; i < SOME_DATA; i++) {
		printf("%c", block[i]);
	}
	printf("\n");
	munmap(block, stat_b.st_size);
	close(fd);
}
