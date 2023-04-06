#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/maxdescendants.h>


#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void spawn_processes(int depth, int *process_count) {
    if (depth > 20 || *process_count >= 50) {
        return;
    }

    pid_t pid = fork();

    if (pid == 0) { // Child process
        printf("Process %d created, depth: %d\n", getpid(), depth);
        (*process_count)++;
        spawn_processes(depth + 1, process_count);

        if (*process_count < 50) {
            pid_t sibling_pid = fork();
            if (sibling_pid == 0) { // Sibling process
                printf("Process %d created, depth: %d\n", getpid(), depth);
                (*process_count)++;
                spawn_processes(depth + 1, process_count);
            } else if (sibling_pid > 0) {
                wait(NULL);
            } else {
                perror("fork");
            }
        }

        _exit(0);
    } else if (pid > 0) { // Parent process
        wait(NULL);
    } else {
        perror("fork");
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

	printf("Search min: %d\n", min);
	printf("Search max: %d\n", max);

	// for(int i = 0; i < 10; ++i)
	// {	
	// 	pid_t pid;
	// 	pid = fork();
	// 	if( pid == 0)
	// 	{
	// 		printf("In child => Own pid : %d\n", getpid());
    //     	printf("In child => Parent's pid : %d\n", getppid());
	// 		sleep(5);
	// 		return 0;
	// 	}
	// 	else{
    //   		printf("In Parent => Child's pid is %d\n", pid);
	// 	    printf("In Parent => Own pid : %d\n", getpid());
    // }
	// }
	int process_count = 1; // Including the initial process
    spawn_processes(1, &process_count);

	pid_t whoMaxDescendants = 0;
	int maxDescendants1 = 0;
	maxDescendants1 = maxDescendants(& whoMaxDescendants, min, max);
	printf("Process %d has the largest number of descendants %d.\n", (int)whoMaxDescendants, maxDescendants1);
	return 0;
}
