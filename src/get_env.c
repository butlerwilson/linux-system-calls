#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{

	if (argc > 2) {
		printf("Paramer count is not right!\n");
		exit (1);
	}
	if (argc == 2) {
		char buffer[128], *p;
		p = getenv(*argv);
		if (p)
			puts(p);
	}

	return 0;
}
