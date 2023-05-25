#include "char.h"
void testCharTrans()
{
	//字符转数字
	char chs[10] = "433";
	int aNum =  10;
	double aDouble = 0.11;
	aNum = atoi(chs);
	aDouble = atof(chs);
	printf("转换后aNum = %f\n", aDouble);

	//数字转字符
	char dataTC[5] = "sss";
	//sprintf(dataTC, "%d", aNum);
	_itoa(aNum, dataTC, 10);
	printf("int 转 char[] %s", dataTC);
}

void getLine(char*  buffer, int len)
{
	int i = 0;
	char character;
	do {
		character = getchar();
		buffer[i++] = character;
		if (i > len - 2)
		{
			break;
		}
	} while (character != '\n');
	buffer[i] = '\0';
}


bool alphabetic(const char c)
{
	if ((c >= 'a' && c <= 'z') || c >= 'A' && c <= 'Z') {
		return true;
	}
	return false;
}

int countWords(const char* String)
{
	int count = 0, index = 0;
	bool flag = true; //用来判断一个单词是否找完
	while (String[index] != '\0') {
		if (alphabetic(String[index]) || (String[index] == '`' && alphabetic(String[index + 1]))) 
		{
			if (flag) {  //判断找到了一个单词
				count++;
				flag = false; //保证将这个单词读取完毕
			}
		}
		else {
			flag = true;
		}
		index++;
	}
	return count;
}

void concat(char* result, const char* str1, const char* str2)
{
	int i = 0, j = 0; //i 应该在外部定义
	for (i = 0; str1[i] != '\0'; ++i) {
		result[i] = str1[i];
	}
	for (j = 0; str2[j] != '\0'; ++j) {
		result[i++] = str2[j];
	}
	result[i] = '\0';
}

int length(const char* String)
{
	int len = 0;
	while (String[len] != '\0') {
		len++;
	}
	return len;
}



void test1()
{
	char buffer[100];
	getLine(buffer, 100);
	int count = countWords(buffer);
	printf("单词个数 : %d", count);
}

void test2()
{
	char result[20];
	char str1[10] = "homeg";
	char str2[10] = "work";

	//拼接
	//concat(result, str1, str2);
	//puts(result);
	
	//个数
	printf("单词的个数：%d", length(str1));


}


