#include <stdio.h>
/*
*	* binds to s right-to-left, it comes first, value at location is read
*	++ on the left binds to the value of s, not location, it is incremented	
*	++ on the right binds to s, the address (pointer). The address(location) is incremented
*/

/*After the unary operator come basic math operators, (*)(/)(%), then +-, associativity is left to right */
int main()
{
	char string[] = "Greetings from the digital realm!\n";
	char *s;

	s = string;
	while (*s)
	{
		putchar(++*s++);
	}

	return (0);
}
