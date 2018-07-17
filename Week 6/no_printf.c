#include <unistd.h>

int main(void) {
	// look ma, no printf
	char* text = "Hello World\n";
	write(1, text, 13);
	return 0;
}
