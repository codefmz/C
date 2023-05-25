#pragma once
//测试通用工具库

#include <stdio.h>
#include <stdlib.h>

void sign_off(void);


void too_bad(void);

/**
* @brief  :测试 exit 与 atexit
* @author :fmw
* @date   :
**/
void testExitAndATexit();


void testQSort();

/**
* @brief  :int 比较函数
* @author :fmw
* @date   :
**/
int compare(const void* a, const void* b);


void testAssert();


double sum(int, ...);

void testSum();