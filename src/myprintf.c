#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

void printf_(const char* p, ...)
{
	int i = 0;
	int num;
	char ch, str[20];
	va_list stack;

	va_start(stack, p);

	for (i = 0; p[i]; i++) {
		if (p[i] == '%') {
			i++;
			switch (p[i]) {
				case 'c':
					ch = va_arg(stack, char);
					putchar(ch);
					break;
				case 'd':
					num = va_arg(stack, int);
					printf("%d", num);
					break;
				case 's':
					strcpy(str, va_arg(stack, char*));
					puts(str);
				default :
					printf("arguments error!\n");
			}
		}
	}

	va_end(stack);

}


int main()
{
	printf_("%c", 'c');

	return 0;
}
