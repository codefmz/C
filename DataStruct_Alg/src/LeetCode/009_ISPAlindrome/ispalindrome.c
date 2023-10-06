#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int reverse(int x)
{
    int r = 0;
    int res = 0;

    while (x != 0) {
        r = x % 10;
        if (res > INT_MAX / 10) {
            return 0;
        }
        res = 10 * res + r;
        x = x / 10;
    }
    return res;
}

static bool isPalindrome(int x)
{
    if (x == 0) {
        return true;
    }
    if (x < 0) {
        return false;
    }
    return x == reverse(x);
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        fprintf(stderr, "Usage: ./test number\n");
        exit(-1);
    }

    printf("%s\n", isPalindrome(atoi(argv[1])) ? "true" : "false");
    return 0;
}