#include "assert.h"
#include <bitmap.h>

int main(int argc, char** argv)
{
    uint32_t bitMap[4] = { 0 };
    uint32_t bit = 0;

    SetBit(bitMap, 1);

    bit = GetBit(bitMap, 1);
    ASSERT_EQUAL(bit, 1);

    SetBit(bitMap, 11);
    bit = GetBit(bitMap, 11);
    ASSERT_EQUAL(bit, 1);

    bit = GetBit(bitMap, 10);
    ASSERT_EQUAL(bit, 0);
}