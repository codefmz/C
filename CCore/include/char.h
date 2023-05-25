#pragma once
#include "ctype.h"
#include "stdlib.h"
#include "stdio.h"


/**
* @brief  : 测试char数组转int、double, int、double转char数组
* @author :fmw
* @date   :2023-3-21 16:50:22
**/
void testCharTrans();

/**
* @brief  :获取标准输入一行字符串
* @author :fmw
* @date   :2023-3-21 17:33:13
**/
void getLine(char * buffer, int len);

/**
* @brief  :判断字符是字符
* @author :fmw
* @date   :2023-3-21 17:35:42
**/
bool alphabetic(const char c);

/**
* @brief  :统计String中英文单词的个数
* @author :fmw
* @date   :2023-3-21 17:47:04
**/
int countWords(const char* String);

/**
* @brief  :字符拼接
* @author :fmw
* @date   :2023-3-21 17:49:27
**/
void concat(char* result, const char* str1, const char* str2);

/**
* @brief  :
* @author :fmw
* @date   :2023-3-21 18:03:13
**/
int length(const char * String);

/**
* @brief  :统计输入一行中的单词个数
* @author :fmw
* @date   :2023-3-21 18:00:36
**/
void test1();

/**
* @brief  :字符拼接、插入、删除、查找
* @author :fmw
* @date   :2023-3-21 18:01:21
**/
void test2();

