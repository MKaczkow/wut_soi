#include <stdio.h>
#include <unistd.h>
#include <sys/maxchildren.h>

int main(void)
{
	for(int i = 0; i < 10; ++i)
	{
		if( fork() == 0)
		{
			sleep(5);
			return 0;
		}
	}
	pid_t whoMaxChildren = 0;
	int maxChildren1 = 0;
	maxChildren1 = maxChildren(& whoMaxChildren);
	printf("Process %d has the largest number of descendants %d.\n", (int)whoMaxChildren, maxChildren1);
	return 0;
}
