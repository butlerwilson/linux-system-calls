#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>

void compipe(void)
{
	pid_t childpid;
	int fd1[2];
	int fd2[2];
	char str1[] = "I love you, chenyn! ";
	char str2[] = "I love you, youngcy! ";

	if (pipe(fd1) < 0 || pipe(fd2) < 0)
		perror("");
	childpid = fork();
	if(childpid > 0) {
		write(fd1[1],str1, sizeof(str1));
		fprintf(stdout,"%s","This info comes from chenyn: ");
		read(fd2[0], str2, sizeof(str2));
		write(1, str2, sizeof(str2));
		printf("\n");
	} else if (childpid == 0) {
		fprintf(stdout, "%s", "This info comes from youngcy: ");
		read(fd1[0], str1, sizeof(str1));
		write(1, str1, sizeof(str1));
		printf("\n");
		write(fd2[1], str2, sizeof(str2));
	} else {
		perror(" ");
		exit(-1);
	}

}

int main()
{
	compipe();

	return 0;
}

