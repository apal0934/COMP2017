#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>

pid_t pid;
char* name;

void child_sigint(int sig) {
	// not signal safe!
	printf("%s: I'm AMAZING\n", name);
}

void child_sighup(int sig) {
	// not signal safe!
	printf("%s: I'm going outside!\n", name);
	exit(0);
}

void parent_sigint(int sig) { 
	// send SIGINT to child
	kill(pid, SIGINT);
}

void child() {
	// SIGHUP
	signal(SIGHUP, child_sighup);
	// SIGINT
	signal(SIGINT, child_sigint);
	name = "CHILD";

	while (1) {
		pause();
	}
}

void parent() {
	name = "PARENT";
	wait(NULL);
}

int main(int argc, char** argv) {
	pid = fork();

	if (pid < 0) {
		perror("Unable to fork");
	} else if (pid == 0) {
		child();
	} else {
		parent();
	}
	
	return 0;
}
	
