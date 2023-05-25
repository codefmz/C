#pragma once
#include <stdio.h>
#include <string.h>

#define MAXTITL 41 /* 书名的最大长度 + 1 */
#define MAXAUTL 31 /* 作者姓名的最大长度 + 1*/


extern struct book;

struct namect {
	char* fname; // 用指针代替数组
	char* lname;
	int letters;
};

void createBook();

void getinfo(struct namect* pst);

/**
* @brief  :保存结构体
* @author :fmw
* @date   :
**/
void saveStruct();

/**
* @brief  :从文件中以二进制流的方式读文件
* @author :fmw
* @date   :
**/
void readStruct();

/**
* @brief  :暂时没有方法处理结构体带指针的深拷贝
* @author :fmw
* @date   :
**/
void saveStructDeeply();

void readStructDeeply();