#include "stdio.h"
#include "string.h"
#include "print.h"
#include "function.h"
#include "char.h"
#include "rand.h"
#include "memory.h"
#include "file.h"
#include "struct.h"
#include "general.h"

#define PR(...) printf(__VA_ARGS__)

void swap(int* p1, int* p2)
{
	*p1 = *p1 ^ *p2;
	*p2 = *p2 ^ *p1;
	*p1 = *p1 ^ *p2;
}


void selectSort(int arr[], int len)
{
	int maxIndex;
	for (int i = 0; i < len - 1; i++)
	{
		maxIndex = i;
		for (int j = i + 1; j < len; j++)
		{
			if (arr[j] < arr[maxIndex])
			{
				maxIndex = j;
			}
		}
		if (i != maxIndex)
		{
			swap(arr + i, arr + maxIndex);
		}
	}
}

int main(int argc, char* argv[])
{

	char str[10] = "中文";
	printf("%s(%d) %s   %s", __FILE__, __LINE__, __func__, str);
}