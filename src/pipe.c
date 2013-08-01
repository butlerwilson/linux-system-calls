#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>

void compipe()
{
	pid_t childpid;

	int fd;
	char str[]= "I love You, chenyn!";
	childpid = fork();
	if (childpid > 0) {
		fd = open("./passwd", O_CREAT | O_RDWR, S_IRUSR); 
		if (fd > 0) {
			write(fd, str, sizeof(str));

			sleep(1);
			close(fd);
		}else {
			perror("ERROR");
			exit(0);
		}
	}
	else if (childpid == 0){
		fd = open("./passwd", O_RDONLY);
		if (fd > 0) {
			read(fd, str, sizeof(str));
			write(1, str, sizeof(str));
		}else {
			perror(" ");
			exit(0);
		}
	}
	else {
		perror("");
		exit(0);
	}
}


int main()
{

	compipe();

	return 0;
}
