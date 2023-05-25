#pragma once
#include "stdio.h"
extern int roll_count;

/**
* @brief  :生成随机数
* @author :fmw
* @date   :
**/
unsigned  int rand0(void);

/**
* @brief  :设置种子
* @author :fmw
* @date   :
**/
void srand1(unsigned int seed);

void testRand();


static int rollem(int sides);

int roll_n_dice(int dice, int sides);

/**
* @brief  :丢筛子程序
* @author :fmw
* @date   :
**/
void testDice();