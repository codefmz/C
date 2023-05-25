#include "function.h"
void starbar(void)
{
	int count;
	for (count = 1; count <= WIDTH; count++)
		putchar('*');
	putchar('\n');
}

void test()
{
	starbar();
	printf("%s\n", NAME);
	printf("%s\n", ADDRESS);
	printf("%s\n", PLACE);
	starbar(); /* Ê¹ÓÃº¯Êý */
}
