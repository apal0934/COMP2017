// note, not meant to work

#include <stdio.h>

int* square_sum(int a, int b);

int main() {
	int* c = square_sum(1, 2);
	printf("%d\n", *c);
	return 1;
}

int* square_sum(int a, int b) {
	int c = 0;
	c += a * a;
	c += b * b;
	return &c;
}
