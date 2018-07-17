#include "arrays.c"


void memecpy(void* destination, void* source, const size_t n_bytes) {
	char* destp = (char*) destination;
	char* sourcep = (char*) source;
	for (unsigned int i = 0; i < n_bytes; i++) {
		destp[i] = sourcep[i];
	}
	return;
}

int main(void) {
	int a[5] = {1,2,3,4,5};
	int b[5];
	memecpy(b, a, sizeof(int) * 5);
	print_int_array(b, 5);
	return 0;
}

