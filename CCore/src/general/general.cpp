#include "general.h"
#define NDEBUG
#include "assert.h"
#include "math.h"
#include "stdarg.h"

void sign_off(void)
{
	puts("Thus terminates another magnificent program from");
	puts("SeeSaw Software!");
}

void too_bad(void)
{
	puts("SeeSaw Software extends its heartfelt condolences");
	puts("to you upon the failure of your program.");
}

void testExitAndATexit()
{
	int n;
	atexit(sign_off); /* 注册 sign_off()函数 */
	puts("Enter an integer:");
	if (scanf("%d", &n) != 1)
	{
		puts("That's no integer!");
		atexit(too_bad); /* 注册 too_bad()函数 */
		exit(EXIT_FAILURE);
	}
	printf("%d is %s.\n", n, (n % 2 == 0) ? "even" : "odd");
}

void testQSort()
{
	int num[10] = { 1,5,2,3,0,5,7,8,10,-10};
	qsort(num, 10, sizeof(int), &compare);
}


int compare(const void* a, const void* b)
{
	const int* a1 = (const int*)a;
	const int* b1 = (const int*)b;
	if (*a1 < *b1)
		return -1;
	else if (*a1 == *b1)
		return 0;
	else
		return 1;
}

void testAssert()
{
	double x, y, z;
	puts("Enter a pair of numbers (0 0 to quit): ");
	while (scanf("%lf%lf", &x, &y) == 2 && (x != 0 || y != 0))
	{
		z = x * x - y * y; /* 应该用 + */
		assert(z >= 0);
		printf("answer is %f\n", sqrt(z));
		puts("Next pair of numbers: ");
	}
	puts("Done");
}

double sum(int lim, ...)
{
	va_list ap;
	double tot = 0;
	int i;
	va_start(ap, lim);
	for (i = 0; i < lim; i++)
	{
		tot += va_arg(ap, double);
	}
	va_end(ap);
	return tot;
}

void testSum()
{
	double s, t;
	s = sum(3, 1.1, 2.5, 13.3);
	t = sum(6, 1.1, 2.1, 13.1, 4.1, 5.1, 6.1);
	printf("return value for sum(3, 1.1, 2.5, 13.3): %g\n", s);
	printf("return value for sum(6, 1.1, 2.1, 13.1, 4.1, 5.1, 6.1): %g\n", t);
}
