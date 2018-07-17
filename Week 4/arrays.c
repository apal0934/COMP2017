#include <stdlib.h>
#include <stdio.h>

void print_int_array(int* arr, const size_t len) {
	for (unsigned int i = 0; i < len; i++) {
		printf("%d\n", arr[i]);
	}
	return;
}

//int main(void) {
//	int a[10];
//	for (int i = 0; i < 10; i++) {
//		a[i] = i + 1;
//	}
//	print_int_array(a, 10);
//	return 0;
//}

