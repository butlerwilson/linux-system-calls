#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>

#define   

int pc = 0;

void catch_zombies(int sig)
{
	wait();
	pc--;
}

void main_prom()
{
	pid_t pid;
	pid = fork();
	switch (pid) {
	case 0:
		//child process

	case -1:
		perror("===");
		exit(-1);
		break;
	default:
		//parent process
	}
}
