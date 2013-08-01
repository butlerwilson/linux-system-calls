#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void encrypt(const char *p, char *q);
void dencrypt(const char *p, char *q);

void encrypt(const char *p, char *q)
{
	while (*p) {
		*q = *p + 4;
		p++;
		q++;
	}
	q--;
}

void dencrypt(const char *p, char *q)
{
	while (*p) {
		*q = *p - 4;
		p++;
		q++;
	}
	q--;
}

int main(int argc, char **argv)
{
	char ch[80];
	*argv++;

	if (argc != 3) {
		printf("Paramer is right!\n");
		exit(0);
	} else if (strcmp(*argv, "e") == 0) {
			encrypt(*argv, ch);
			printf("%s\n", ch);
	}
	else if (strcmp(*argv, "d") == 0) {
			dencrypt(*argv, ch);
			printf("%s\n", ch);
	} else {
		printf("The paramer is not right!\n");
		exit(0);
	}

	return 0;
}
