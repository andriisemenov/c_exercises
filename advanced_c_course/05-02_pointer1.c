#include <stdio.h>

int main()
{
	char *string = "Greetings from the digital realm!\n";
	char *s;

	s = string;
	// while (putchar(*s++))
	// 	;
	while (*s)
	{
		putchar(*s++); //Value is dereferenced and then the address is incremented
	}

	return (0);
}
