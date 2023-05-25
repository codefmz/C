#include "rand.h"
#include "time.h"



static unsigned long int next = 1; /* 种子 */

int roll_count = 0; /* 外部链接 */

unsigned  int rand0(void)
{
	/* 生成伪随机数的魔术公式 */
	next = next * 1103515245 + 12345;
	return (unsigned int)(next / 65536) % 32768;
}

void srand1(unsigned int seed)
{
	next = seed;
}



void testRand()
{
	for (int i = 0; i < 100; i++)
	{
		unsigned int temp = rand0();
		printf("%d\n", temp);
	}
	puts("========================");

	next = 1;

	for (int i = 0; i < 100; i++)
	{
		unsigned int temp = rand0();
		printf("%d\n", temp);
	}
}

int rollem(int sides)
{
	int roll;
	roll = rand0() % sides + 1;
	++roll_count; /* 计算函数调用次数 */
	return roll;
}

int roll_n_dice(int dice, int sides)
{
	int d;
	int total = 0;
	if (sides < 2)
	{
		printf("Need at least 2 sides.\n");
		return -2;
	}
	if (dice < 1)
	{
		printf("Need at least 1 die.\n");
		return -1;
	}
	for (d = 0; d < dice; d++)
		total += rollem(sides);
	return total;
}

void testDice()
{
	int dice, roll;
	int sides;
	int status;
	srand1((unsigned int)time(0)); /* 随机种子 */
	printf("Enter the number of sides per die, 0 to stop.\n");
	while (scanf("%d", &sides) == 1 && sides > 0)
	{
		printf("How many dice?\n");
		if ((status = scanf("%d", &dice)) != 1)
		{
				if (status == EOF)
				{ 
					break; /* 退出循环 */
				}
				else
				{
					printf("You should have entered an integer.");
					printf(" Let's begin again.\n");
					while (getchar() != '\n')
						continue; /* 处理错误的输入 */
					printf("How many sides? Enter 0 to stop.\n");
					continue; /* 进入循环的下一轮迭代 */
				}
		}
		roll = roll_n_dice(dice, sides);
		printf("You have rolled a %d using %d %d-sided dice.\n",roll, dice, sides);
		printf("How many sides? Enter 0 to stop.\n");
	}
	printf("The rollem() function was called %d times.\n",
	roll_count); /* 使用外部变量 */
	printf("GOOD FORTUNE TO YOU!\n");
}




