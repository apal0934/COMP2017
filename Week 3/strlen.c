#include <stdio.h>
#include <stdlib.h>

size_t c_strlen(char* str);

int main(int argc, char** argv) {
	if (argc < 2) {
		printf("One argument expected\n");
		return EXIT_FAILURE;
	}

	char* string = argv[1];
	size_t size = c_strlen(string);
	printf("%zu\n", size);

	return EXIT_SUCCESS;
}

size_t c_strlen(char* str) {
	size_t i = 0;
	while (str[i] != '\0') {
		i++;
	}

	return i;
}


