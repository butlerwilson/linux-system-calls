#include <sys/types.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/ipc.h>


int main()
{

	pid_t pid;
	pid = fork();
	int shmid;
	char *sp;
	key_t key = 3414355;

	if(pid > 0) {
		shmid = shmget(key, 128, IPC_CREAT | IPC_EXCL | 0655);
		if(shmid) {
			sp = (char *)shmat(shmid, NULL, 0);
			if(sp)
				strcpy(sp, "hahahahahahahaha     fdfdfdfd ");
			else {
				perror("");
				return -1;
			}
		}else {
			perror("");
			return -1;
		}
	} else if(pid == 0) {
		sleep(1);
		shmid = shmget(key, 128, IPC_EXCL);
		if(shmid) {
			sp = (char *)shmat(shmid, NULL, 0);
			if(sp)
				fprintf(stdout, "%s", sp);
			else {
				perror("");
				return -1;
			}
		} else {
				perror("");
				return -1;
			}
	} else {
		perror("Process create failed");
		return -1;
	}

	return 0;
}
