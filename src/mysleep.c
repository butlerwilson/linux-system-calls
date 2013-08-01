#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void showint()
{
	printf("Time up!\n");
}

void mysleep(unsigned int seconds)
{
	while(1) {
		signal(SIGINT, showint);
		alarm(seconds);
		pause();
	}
}


int main()
{
	int i;

	for(i = 0; i < 100; i++) {
		mysleep(1);
		printf("This is i=[%d]\n", i);
	}

	return 0;
}
