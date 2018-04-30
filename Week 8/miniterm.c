#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(void) {
	char buffer[1024];
	while (1) {
		printf(">");
		fgets(buffer, sizeof(buffer), stdin);
		if (strcmp(buffer, "quit")) {
			break;
		} else {
			system(buffer);
		}
	}
	return 0;
}	
