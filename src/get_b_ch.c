#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

int main()
{
	FILE *fp;
	int dfd;
	unsigned char ch, dch, index = 1<<7;
//	short ch, dch;
	int i = 0, j = 1;

	fp = fopen("source", "r");
	dfd = open("bin", O_WRONLY);

	if (fp && dfd) {
		while (!feof(fp)) {
			dch = '\0'; index = 1 << 7;
			for(i = 0; i < 8; i++) {
				ch = fgetc(fp);
				dch |= (ch - '0') * (1 << (7 - i));
			}
			j++;
			write(dfd, &dch, 1);
 printf("%X ", dch);
		}
printf("%d", j-1);
		close(dfd);
	} else
		printf("OPen file failed!\n");
	return 0;
}
