#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main(void) {
	int pipefd[2];
	if (pipe(pipefd) < 0) {
		perror("unable to create pipe");
		return 1;
	}

	pid_t pid = fork();

	if (pid < 0) { 
		perror("unable to fork");
		return 2;
	}

	if (pid == 0) {
		// we are the child
		close(pipefd[0]);
		time_t current_time = time(NULL);
		printf("Child: Yes I do!\n");
		write(pipefd[1], &current_time, sizeof(current_time));
		close(pipefd[1]);
	
		
	} else {
		// we are the parent
		close(pipefd[1]);
		time_t current_time;
		printf("Parent: Hi! Do you know what time it is?\n");
	       // block until there is data to read	
		read(pipefd[0], &current_time, sizeof(current_time));
		char *c_time_string = ctime(&current_time);
		close(pipefd[0]);
		printf("Parent: Thank you, know I know the time is: %s", c_time_string);

	}

	return 0;
}
