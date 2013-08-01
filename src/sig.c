#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sig(int signal_num)
{
	printf("The patrent process send a message to child!\n");
}

void func()
{
	int fd[2];
	char str[] = "I love you";
	pid_t child, parent;
	pipe(fd);
	child = fork();
	if(child > 0) {
		write(fd[1], str, sizeof(str));
		signal(SIGQUIT, sig);
		while(1) {
			sleep(1);
			printf("ha ");
		}
	} else if(child == 0) {
		read(fd[0],str, sizeof(str));
		printf("This is child process!\n");
		write(1, str, sizeof(str));
	} else
		perror("");
}

int main()
{
	func();

	return 0;
}

