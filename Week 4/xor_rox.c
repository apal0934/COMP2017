#include <stdio.h>

int main(void) {
	int a = 5;
	int b = 3;
 	a ^= b;
	printf("%d\n", a);
	b ^= a;
	printf("%d\n", b);
	a ^= b;
	printf("%d\n", a);
	
	return 0;
}
