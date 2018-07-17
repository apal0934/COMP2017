// note, not meant to work

#include <stdio.h>
#include <stdlib.h>

int* square_sum(int a, int b);

int main() {
	int* c = square_sum(1, 2);
	printf("%d\n", *c);
	free(c);
	return 1;
}

int* square_sum(int a, int b) {
	int* c = malloc(sizeof(int));
	*c = a * a;
	*c += b * b;
	return c;
}
