#include <stdio.h>
#include <unistd.h>

int main(void) {
	int pipefd[2];

	if (pipe(pipefd) < 0) {
		perror("Unable to pipe");
		return 1;
	}

	pid_t pid = fork();

	if (pid < 0) {
		perror("Unable to fork, try spoon");
		return 2;
	} else if (pid == 0) {
		close(pipefd[0]);
		close(1);
		dup(pipefd[1]);
		execlp("ls", "ls", "-l", NULL);
	} else {
		close(pipefd[1]);
		FILE* fp = fdopen(pipefd[0], "r");
		char buffer[8192];
		int i = 0;
		while (1) {
			if (fgets(buffer, sizeof(buffer), fp) == NULL) {
				break;
			}
			i++;
			printf("Line %2d: %s", i, buffer);
		}
	}
	return 0;
}
