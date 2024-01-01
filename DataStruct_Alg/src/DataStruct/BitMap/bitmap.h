#include <stdint.h>

#define SetBit(bitMap, n) (bitMap[(n) >> 5] |= 1 << (n) % 32)

#define GetBit(bitMap, n) (bitMap[n >> 5] >> (n) % 5 & 1)
