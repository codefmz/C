#pragma once
#include "stdio.h"
#include "string.h"
#define PAGES 336
#define WORDS 65618
/*
*  brief : 绘制一个菱形
*  num : 菱形点的个数
*/
void printDiamond(int num);

/*
*  brief : 绘制一个菱形, 中心是空的
*  num : 菱形点的个数
*/
void printDiamondCentralBlank(int num);

/*
*  brief : printf 用法测试
*/
void testPrintf();


/*
*  brief : scanf 用法测试
*/
void testScanf();

/**
* @brief  :
* @author :
* @date   :2023-3-21 14:52:04
**/
void testGetPuts();


#include "rand.h"
void testExtent();