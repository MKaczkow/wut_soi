#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/maxdescendants.h>
#include <sys/types.h>
#include <sys/wait.h>


void spawn_process_line() {

	int pid;
	
	for (int i=0; i<19; i++) {
		pid = fork();
		if (pid == 0) {
			// child process
		}
		else { // parent process
			
			wait(NULL);
			exit(0);
		}
	}
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Usage: %s <min> <max>\n", argv[0]);
        return 1;
    }

    int min = atoi(argv[1]);
    int max = atoi(argv[2]);
	int process_count = 1; // Including the initial process

    spawn_process_line();

	printf("Search min: %d\n", min);
	printf("Search max: %d\n", max);

	pid_t whoMaxDescendants = 0;
	int maxDescendants1 = 0;
	maxDescendants1 = maxDescendants(& whoMaxDescendants, min, max);
	printf("Process %d has the largest number of descendants %d.\n", (int)whoMaxDescendants, maxDescendants1);
	return 0;
}
