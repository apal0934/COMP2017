#include <stdio.h>
#include <stdlib.h>

int* dynamic_array(int length);

int main(int argc, char** argv) {
	if (argc != 2) {
		printf("Exactly one (1) argument expected\n");
		return 1;
	}

	int length = atoi(argv[1]);

	int* array = dynamic_array(length);
	for (int i = 0; i < length; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
	free(array);
	return 0;
}

int* dynamic_array(int length) {
	if (length < 1) {
		printf("Length >= 1 required\n");
		exit(1);
	}
	
	int* array = malloc(sizeof(int) * length);

	for (int i = 0; i < length; i++) {
		array[i] = i * i;
	}

	return array;
}

