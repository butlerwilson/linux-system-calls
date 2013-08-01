#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void creatproc()
{
	int i;
	pid_t pid, fpid;

	fpid = fork();
	for (i = 0; i < 10; i++)
		if(fpid > 0 ) {

			wait(NULL);
			while(1) {
				pid = setsid();
				perror("");
				printf("This id is: %d\n", pid);
				sleep(1);
			}
		} else if(fpid == 0) {
			sleep(1);
			printf("pid=[%d] The child process is runing\n", getpid());
		} else {
			perror("Wrong: ");
			exit(-1);
		}
	printf("The user id is: , the group id is: \n", getuid(), getgid());

}

int main()
{
	creatproc();

	return 0;
}
