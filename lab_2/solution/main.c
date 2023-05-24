#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/maxdescendants.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Usage: %s <firstProcessThreadsInitialSlots> <secondInitialSlots;>\n", argv[0]);
        return 1;
    }

    int firstProcessThreadsInitialSlots = atoi(argv[1]);
    int secondInitialSlots = atoi(argv[2]);
    int process_count = 2; // Including the initial process

    for (int i = 0; i < process_count; i++)
    {
        pid_t pid = fork();
        if (pid == -1)
        {
            perror("fork");
            return 1;
        }
        if (pid == 0)
        {
            // child
            if (i == 0)
            {
                // first process
                // set initial slots number for the process
                // using systemcall setInitialSlotsNumber
                setInitialSlotsNumber(firstProcessThreadsInitialSlots);
            }
            else
            {
                // second process
                // set initial slots number for the process
                // using systemcall setInitialSlotsNumber
                setInitialSlotsNumber(secondInitialSlots);
            }
            break;
        }
    }

    return 0;
}
