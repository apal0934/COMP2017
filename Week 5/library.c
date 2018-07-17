#include <stdio.h>
#include <stdlib.h>
#include "library.h"

struct book* dynamic_array(int length);

int main(int argc, char** argv) {
	if (argc != 2) {
		printf("Exactly one (1) argument expected\n");
		return 1;
	}

	int length = atoi(argv[1]);

	struct book* library = dynamic_array(length);
	for (int i = 0; i < length; i++) {
		printf("%u ", library[i].id);
	}
	printf("\n");
	free(library);
	return 0;
}

struct book* dynamic_array(int length) {
	if (length < 1) {
		printf("Length >= 1 required\n");
		exit(1);
	}
	
	struct book* array = malloc(sizeof(struct book) * length);

	for (int i = 0; i < length; i++) {
		array[i].id = i * i;
	}

	return array;
}

