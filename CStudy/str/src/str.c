#include "str.h"
#include "util.h"
void Test_Str_strchr()
{
    const char* STR = "this is a const str!";
    char* result = strchr(STR, 'a');
    ASSERT_EQUAL(result - STR, 8);
    ASSERT_EQUAL_STR(result, "a const str!");

    result = strrchr(STR, 'o');
    ASSERT_EQUAL(result - STR, 11);
    ASSERT_EQUAL_STR(result, "onst str!");
}