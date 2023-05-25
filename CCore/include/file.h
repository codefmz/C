#pragma once
#include <stdio.h>
#include <stdlib.h> // 提供 exit()的原型

/**
* @brief  :测试 File* fopen putc getc 函数
* @author :fmw
* @date   :
**/
void testFile();
/**
* @brief  :测试复制拷贝文件
* @author :fmw
* @date   :
**/
void testReducto();

/**
* @brief  :fprintf fscanf rewind 用法
* @author :fmw
* @date   :
**/
void addAWord();
/**
* @brief  :使用自动扩容实现读取整个文件
* @author :fmw
* @date   :
**/
void readWholeFile();

/**
* @brief  :倒叙显示文件内容， fseek 与 ftell 的用法
* @author :fmw
* @date   :
**/
void reverse();


void append();

/**
* @brief  :END
* @author :fmw
* @date   :
**/
void append(FILE* source, FILE* dest);


/**
* @brief  :从控制台输入不带 \n 的字符串
* @author :fmw
* @date   :
**/
char* s_gets(char* st, int n);

/**
* @brief  :创建一个 double数组，以二进制格式写入到文件中，并使用随机访问函数根据索引访问
* @author :fmw
* @date   :
**/
void  randbin();