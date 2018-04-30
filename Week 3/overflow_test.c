#include <stdio.h>

int main(void) {
	int array1[4] = { 1, 2, 3, 4 };
	int array2[4] = { 5, 6, 7, 8 };

	int* end;
	
	array1 > array2 ? (end = array1) : (end = array2);

	for (int i = 7; i >= 0; i--) {
		printf("%d\n", end[i]);
	}
}

