#include <stdio.h>

typedef void (*new_func)(int);

void jchen(int m)
{
	int i;
	double num = 1;

	for (i = 0; i <= m; i++)
		num *= i;
	printf("%.2lf", num);
}


int main(int argc, char **argv)
{
	new_func fp;
	fp(*argv[1]);

}
