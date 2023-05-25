#include "memory.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
int static_store = 30;
const char* pcg = "String Literal";

void testMallocAndFree()
{
	int n;
	double* ptd = nullptr;
	int max;
	int number;
	int i = 0;
	puts("What is the maximum number of type double entries?");
	if (scanf("%d", &max) != 1)
	{
		puts("Number not correctly entered -- bye.");
		exit(EXIT_FAILURE);
	}
	ptd = (double*)malloc(max * sizeof(double));
	if (ptd == NULL)
	{
		puts("Memory allocation failed. Goodbye.");
		exit(EXIT_FAILURE);
	}
	/* ptd 现在指向有max个元素的数组 */
	puts("Enter the values (q to quit):");
	while (i < max && scanf("%lf", &ptd[i]) == 1)
		++i;
	printf("Here are your %d entries:\n", number = i);
	for (i = 0; i < number; i++)
	{
		printf("%7.2f ", ptd[i]);
		if (i % 7 == 6)
			putchar('\n');
	}
	if (i % 7 != 0)
		putchar('\n');
	puts("Done.");
	free(ptd);
}

void testWhereMeomry()
{
	int auto_store = 40;
	char auto_string[] = "Auto char Array";
	int* pi = NULL;
	char* pcl;
	pi = (int*)malloc(sizeof(int));
	*pi = 35;
	pcl = (char*)malloc(strlen("Dynamic String") + 1);
	strcpy(pcl, "Dynamic String");
	printf("static_store: %d at %p\n", static_store, &static_store);
	printf(" auto_store: %d at %p\n", auto_store, &auto_store);
	printf(" *pi: %d at %p\n", *pi, pi);
	printf(" %s at %p\n", pcg, pcg);
	printf(" %s at %p\n", auto_string, auto_string);
	printf(" %s at %p\n", pcl, pcl);
	printf(" %s at %p\n", "Quoted String", "Quoted String");
	free(pi);
	free(pcl);

	

}

void testConst()
{
	const float* pf; /* pf 指向一个float类型的const值 */
	float * const pt = NULL; /* pt 是一个const指针 */
	const float const * ptr;

	//*pf = 100;
	//pf = NULL;
	//*pt = 10;
	//pt = NULL;

}
