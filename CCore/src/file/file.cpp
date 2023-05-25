#include "file.h"
#include "string.h"
#define LEN 40
void testFile()
{
    int ch; // 读取文件时，储存每个字符的地方
    FILE* fp; // “文件指针”
    unsigned long count = 0;
    char fileName[100]= R"(E:\Code\C\.gitignore)";
    //printf("输入需要读取的文件名：");
    //fgets(fileName, 80, stdin);


    //int len = strlen(fileName);
    //fileName[len - 1] = '\0';

    if ((fp = fopen(fileName, "r")) == NULL)
    {
        printf("Can't open %s\n", fileName);
        exit(EXIT_FAILURE);
    }

    char buffer[100] = { 0 };
    int row = 0;

    while (fgets(buffer, 99, fp) != NULL)
    {
        fputs(buffer,stdout);
        row++;
    }

    while ((ch = getc(fp)) != EOF)
    {
        putc(ch, stdout); // 与 putchar(ch); 相同
        count++;
    }


    fclose(fp);
    printf("File %s has %lu characters\n", fileName, row);
}

void testReducto()
{
    FILE* in, * out; // 声明两个指向 FILE 的指针
    int ch;
    char name[LEN] = R"(E:\Code\C\.gitignore)";; // 储存输出文件名
    int count = 0;

    // 设置输入
    if ((in = fopen(name, "r")) == NULL)
    {
        fprintf(stderr, "I couldn't open the file \"%s\"\n", name);
        exit(EXIT_FAILURE);
    }

    strcat(name, ".red"); // 在文件名后添加.red
    if ((out = fopen(name, "w")) == NULL)
    { 
        // 以写模式打开文件
        fprintf(stderr, "Can't create output file.\n");
        exit(3);
    }

    // 拷贝数据
    while ((ch = getc(in)) != EOF)
        if (count++ % 3 == 0)
            putc(ch, out);// 打印3个字符中的第1个字符

    // 收尾工作
    if (fclose(in) != 0 || fclose(out) != 0)
    {
        fprintf(stderr, "Error in closing files\n");
    }   
}

#define MAX 41
#define FILEPATH  R"(E:\Code\C\test.txt)"
void addAWord()
{
    FILE* fp;
    char words[MAX] = FILEPATH;
    if ((fp = fopen(FILEPATH, "a+")) == NULL)
    {
        fprintf(stdout, "Can't open \"wordy\" file.\n");
        exit(EXIT_FAILURE);
    }
    puts("Enter words to add to the file; press the #");
    puts("key at the beginning of a line to terminate.");
    while ((fscanf(stdin, "%40s", words) == 1) && (words[0] != '#'))
        fprintf(fp, "%s\n", words);
    puts("File contents:");
    rewind(fp); /* 返回到文件开始处 */
    while (fscanf(fp, "%s", words) == 1)
        puts(words);
    puts("Done!");
    if (fclose(fp) != 0)
        fprintf(stderr, "Error closing file\n");
}

void readWholeFile()
{
    FILE* p;
    if ((p = fopen(FILEPATH, "r")) == NULL)
    {
        fprintf(stdout, "Can't open \"wordy\" file.\n");
        exit(EXIT_FAILURE);
    }

    int initSize = 10;
    char* buffer = new char[initSize];
    int count = 0;
    char temp;
    while ((temp = getc(p)) != EOF)
    {
        buffer[count++] = temp;
        if (count > initSize - 1)
        {
            initSize *= 2;
            char * pc = new char[initSize];
            memcpy(pc, buffer, initSize);
            delete buffer;
            buffer = pc;
        }
    }
    buffer[count] = '\0';
    puts(buffer);
    printf("=========");

}
#define CNTL_Z '\032' /* DOS文本文件中的文件结尾标记 */
#define SLEN 81
void reverse()
{
    char file[SLEN] = FILEPATH;
    char ch;
    FILE* fp;
    long count, last;
    //puts("Enter the name of the file to be processed:");
    //scanf("%80s", file);
    if ((fp = fopen(file, "rb")) == NULL)
    { /* 只读模式 */
        printf("reverse can't open %s\n", file);
        exit(EXIT_FAILURE);
    }
    fseek(fp, 0L, SEEK_END); /* 定位到文件末尾 */
    last = ftell(fp);
    for (count = 1L; count <= last; count++)
    {
        fseek(fp, -count, SEEK_END); /* 回退 */
        ch = getc(fp);
        if (ch != CNTL_Z && ch != '\r') /* MS-DOS 文件 */
            putchar(ch);
    }
    putchar('\n');
    fclose(fp);
}

#define BUFSIZE 4096
#define SLEN 81
void append()
{
    FILE* fa, * fs; // fa 指向目标文件，fs 指向源文件
    int files = 0; // 附加的文件数量
    char file_app[SLEN]; // 目标文件名
    char file_src[SLEN]; // 源文件名
    int ch;
    puts("Enter name of destination file:");
    s_gets(file_app, SLEN);
    if ((fa = fopen(file_app, "a+")) == NULL)
    {
        fprintf(stderr, "Can't open %s\n", file_app);
        exit(EXIT_FAILURE);
    }
    if (setvbuf(fa, NULL, _IOFBF, BUFSIZE) != 0)
    {
        fputs("Can't create output buffer\n", stderr);
        exit(EXIT_FAILURE);
    }
    puts("Enter name of first source file (empty line to quit):");
    while (s_gets(file_src, SLEN) && file_src[0] != '\0')
    {
        if (strcmp(file_src, file_app) == 0)
            fputs("Can't append file to itself\n", stderr);
        else if ((fs = fopen(file_src, "r")) == NULL)
            fprintf(stderr, "Can't open %s\n", file_src);
        else
        {
            if (setvbuf(fs, NULL, _IOFBF, BUFSIZE) != 0)
            {
                fputs("Can't create input buffer\n", stderr);
                continue;
            }
            append(fs, fa);
            if (ferror(fs) != 0)
                fprintf(stderr, "Error in reading file %s.\n",file_src);
            if (ferror(fa) != 0)
                fprintf(stderr, "Error in writing file %s.\n",file_app);
            fclose(fs);
            files++;
            printf("File %s appended.\n", file_src);
            puts("Next file (empty line to quit):");
        }
    }
    printf("Done appending.%d files appended.\n", files);
    rewind(fa);
    printf("%s contents:\n", file_app);
    while ((ch = getc(fa)) != EOF)
        putchar(ch);
    puts("Done displaying.");
    fclose(fa);
}

void append(FILE* source, FILE* dest)
{
    size_t bytes;
    static char temp[BUFSIZE]; // 只分配一次
    
    while ((bytes = fread(temp, sizeof(char), BUFSIZE, source)) > 0)
        fwrite(temp, sizeof(char), bytes, dest);
}

char* s_gets(char* st, int n)
{
    char* ret_val;
    char* find;
    ret_val = fgets(st, n, stdin);
    if (ret_val)
    {
        find = strchr(st, '\n'); // 查找换行符, 返回这个字符的位置
        if (find) // 如果地址不是NULL，
            *find = '\0'; // 在此处放置一个空字符
        else
            while (getchar() != '\n')
                continue;
    }
    return ret_val;
}

#define ARSIZE 1000
void randbin()
{
    double numbers[ARSIZE];
    double value;
    const char* file = "numbers.dat";
    int i;
    long pos;
    FILE* iofile;
    // 创建一组 double类型的值
    for (i = 0; i < ARSIZE; i++)
        numbers[i] = 100.0 * i + 1.0 / (i + 1);
    // 尝试打开文件
    if ((iofile = fopen(file, "wb")) == NULL)
    {
        fprintf(stderr, "Could not open %s for output.\n", file);
        exit(EXIT_FAILURE);
    }
    // 以二进制格式把数组写入文件
    fwrite(numbers, sizeof(double), ARSIZE, iofile);

    fclose(iofile);
    if ((iofile = fopen(file, "rb")) == NULL)
    {
        fprintf(stderr,
            "Could not open %s for random access.\n", file);
        exit(EXIT_FAILURE);
    }
    // 从文件中读取选定的内容
    printf("Enter an index in the range 0-%d.\n", ARSIZE - 1);
    while (scanf("%d", &i) == 1 && i >= 0 && i < ARSIZE)
    {
        pos = (long)i * sizeof(double); // 计算偏移量
        fseek(iofile, pos, SEEK_SET); // 定位到此处
        fread(&value, sizeof(double), 1, iofile);
        printf("The value there is %f.\n", value);
        printf("Next index (out of range to quit):\n");
    }
    // 完成
    fclose(iofile);
    puts("Bye!");
}
