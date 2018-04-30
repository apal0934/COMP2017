#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse_string(char* str);

int main(void) {
	
	char string[1024];
	
	fgets(string, sizeof(string), stdin);
	
	reverse_string(string);
	printf("%s\n", string);
	return EXIT_SUCCESS;

}

void reverse_string(char* str) {
	char temp;
	for (int start = 0, end = strlen(str) - 1; start <= end; start++, end--) {
		temp = str[start];
		str[start] = str[end];
		str[end] = temp;
	}
}	
