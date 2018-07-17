// point of this is that it doesn't work

#include <stdio.h>

int main() {
	int original_array[10];
	int copied_array[10];
	for (int i = 0; i < 10; i++) {
		original_array[i] = i * i;
	}

	copied_array = original_array;

	for (int i = 0; i < 10; i++) {
		original_array[i] = i * i;
	}

	for (int i = 0; i < 10; i++) {
		printf("%d %d\n", original_array[i], copied_array[i]);
	}

}
