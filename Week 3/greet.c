#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	if (argc < 2) {
		printf("One argument expected\n");
		return EXIT_FAILURE;
	}
	
	char* greeter = argv[1];
	char name[1024];
	printf("What is your name? ");
	scanf("%s", name);

	printf("%s %s\n", greeter, name);
	return EXIT_SUCCESS;
}
