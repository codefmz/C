#include "print.h"
void printDiamond(int num)
{
	for (int i = 0; i < num; i++)
	{
		if (i <= num / 2)
		{
			int j = 0;
			for (; j < num / 2 - i; j++)
			{
				printf(" ");
			}
			for (; j <= num / 2 + i; j++)
			{
				printf("*");
			}
			for (; j < num; j++)
			{
				printf(" ");
			}
			printf("\n");
		}
		else
		{
			int j = 0;
			for (; j < i - num / 2; j++)
			{
				printf(" ");
			}
			for (; j < 3 * num / 2 - i; j++)
			{
				printf("*");
			}
			for (; j < num; j++)
			{
				printf(" ");
			}
			printf("\n");
		}
	}
}


void printDiamondCentralBlank(int num)
{
	for (int i = 0; i < num; i++)
	{
		if (i <= num / 2)
		{
			int j = 0;
			for (; j < num / 2 - i; j++)
			{
				printf(" ");
			}
			for (; j <= num / 2 + i; j++)
			{
				if ((j == num / 2 - i) || (j == num / 2 + i))
				{
					printf("*");
				}
				else
				{
					printf(" ");
				}
			}
			for (; j < num; j++)
			{
				printf(" ");
			}
			printf("\n");
		}
		else
		{
			int j = 0;
			for (; j < i - num / 2; j++)
			{
				printf(" ");
			}
			for (; j < 3 * num / 2 - i; j++)
			{
				if ((j == i - num / 2) || (j == 3 * num / 2 - i - 1))
				{
					printf("*");
				}
				else
				{
					printf(" ");
				}
			}
			for (; j < num; j++)
			{
				printf(" ");
			}
			printf("\n");
		}
	}
}

void testPrintf()
{
	short num = PAGES;
	short mnum = -PAGES;
	int z = PAGES;
	char zc = 80;
	char numc = PAGES;
	printf("num as short and unsigned short: %hd %hu\n", num, num);
	printf("-num as short and unsigned short: %hd %hu\n", mnum, mnum);
	printf("num as int and char: %d %c\n", num, num);
	printf("char z = %c   cnum = %c\n", zc, numc);
	printf("WORDS as int, short, and char: %d %hd %c\n", WORDS, WORDS, WORDS);
}

void testScanf()
{
	int age; // 变量
	float assets; // 变量
	char pet[30]; // 字符数组，用于储存字符串
	pet[1] = '\0';

	printf(" age =  ");
	scanf("%d", &age);
	printf("second scanf : ass = ");
	scanf("%c", pet);
	printf("%s", pet);
	printf("%s", pet);
	printf("%s", pet);
}

void testGetPuts()
{
	printf("输入一行内容：");
	char s[90];
	fgets(s, strlen(s), stdin);
	fputs(s,stdout);
}

void testExtent()
{
	roll_count = 100;
}
