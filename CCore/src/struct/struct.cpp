#include "struct.h"
#include "file.h"

#define SAVEPATH R"(library.txt)"
struct book{ /* 结构模版：标记是 book */
	char title[MAXTITL];
	char author[MAXAUTL];
	float value;
}; /* 结构模版结束 */

void createBook()
{
	struct book library; /* 把 library 声明为一个 book 类型的变量 */
	printf("Please enter the book title.\n");
	s_gets(library.title, MAXTITL); /* 访问title部分*/
	printf("Now enter the author.\n");
	s_gets(library.author, MAXAUTL);
	printf("Now enter the value.\n");
	scanf("%f", &library.value);
	printf("%s by %s: $%.2f\n", library.title,
		library.author, library.value);
	printf("%s: \"%s\" ($%.2f)\n", library.author,
		library.title, library.value);
	printf("Done.\n");
}

#define SLEN 81
void getinfo(namect* pst)
{
	char temp[SLEN];
	printf("Please enter your first name.\n");
	s_gets(temp, SLEN);
	// 分配内存储存名
	pst->fname = (char*)malloc(strlen(temp) + 1);
	// 把名拷贝到已分配的内存
	strcpy(pst->fname, temp);
	printf("Please enter your last name.\n");
	s_gets(temp, SLEN);
	pst->lname = (char*)malloc(strlen(temp) + 1);
	strcpy(pst->lname, temp);
}

void saveStruct()
{
	book library[4] = { {"狂人日记", "周树人", 29.9}, {"钢铁是怎样炼成的", "奥.耶夫斯基", 9.9},
	{"自控力", "凯利", 99.9}, {"心流", "米哈里", 49.0} };
	FILE * pf;
	if ((pf = fopen(SAVEPATH, "wb")) == NULL)
	{
		printf("can't open file : %s", SAVEPATH);
		exit(EXIT_FAILURE);
	}
	fwrite(library, sizeof(book), 4,pf);
	fclose(pf);
}
void readStruct()
{
	book library[4];
	FILE* pf;
	if ((pf = fopen(SAVEPATH, "r")) == NULL)
	{
		printf("can't open file : %s", SAVEPATH);
		exit(EXIT_FAILURE);
	}
	fread(library, sizeof(book), 4, pf);
	fclose(pf);
	for (size_t i = 0; i < 4; i++)
	{
		puts(library[i].title);
	}
}

void saveStructDeeply()
{
	namect library[2]; /*= { {"狂人日记", "周树人", 29.9}, {"钢铁是怎样炼成的", "奥.耶夫斯基", 9.9},
{"自控力", "凯利", 99.9}, {"心流", "米哈里", 49.0} };*/

	library[0].fname = new char[10]{ "狂人日" };
	library[0].lname = new char[10]{ "周树人" };
	library[0].letters = 29;
	
	library[1].fname = new char[20]{ "钢铁是怎样炼成的"};
	library[1].lname = new char[20]{ "奥.耶夫斯基" };
	library[1].letters = 300;

	FILE* pf;
	if ((pf = fopen(SAVEPATH, "wb")) == NULL)
	{
		printf("can't open file : %s", SAVEPATH);
		exit(EXIT_FAILURE);
	}
	printf(" sizeof(library) = %d \n", sizeof(char *));
	for (int i = 0; i < 2; i++)
	{
		printf(" sizeof(library[%d]) = %d \n",i,  sizeof(library[i]));
	}
	fwrite(library, sizeof(book), 2, pf);
	fclose(pf);
}

void readStructDeeply()
{
}
