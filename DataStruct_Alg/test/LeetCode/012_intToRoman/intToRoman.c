#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ToRoman(int num1, char* s, int index)
{
    if (num1 == 0) {
        s[index] = '\0';
        return;
    }
    int times = 0;
    if (num1 >= 1000) {
        s[index++] = 'M';
        return ToRoman(num1 - 1000, s, index);
    } else if (num1 >= 900) {
        s[index++] = 'C';
        s[index++] = 'M';
        return ToRoman(num1 - 900, s, index);
    } else if (num1 >= 500) {
        s[index++] = 'D';
        times = (num1 - 500) / 100;
        for (; times > 0; --times) {
            s[index++] = 'C';
        }
        return ToRoman(num1 % 100, s, index);
    } else if (num1 >= 400) {
        s[index++] = 'C';
        s[index++] = 'D';
        return ToRoman(num1 - 400, s, index);
    } else if (num1 >= 100) {
        times = num1 / 100;
        for (; times > 0; --times) {
            s[index++] = 'C';
        }
        return ToRoman(num1 % 100, s, index);
    } else if (num1 >= 90) {
        s[index++] = 'X';
        s[index++] = 'C';
        return ToRoman(num1 - 90, s, index);
    } else if (num1 >= 50) {
        s[index++] = 'L';
        times = (num1 - 50) / 10;
        for (; times > 0; --times) {
            s[index++] = 'X';
        }
        return ToRoman(num1 % 10, s, index);
    } else if (num1 >= 40) {
        s[index++] = 'X';
        s[index++] = 'L';
        return ToRoman(num1 - 40, s, index);
    } else if (num1 >= 10) {
        times = num1 / 10;
        for (; times > 0; --times) {
            s[index++] = 'X';
        }
        return ToRoman(num1 % 10, s, index);
    } else if (num1 >= 9) {
        s[index++] = 'I';
        s[index++] = 'X';
        return ToRoman(num1 - 9, s, index);
    } else if (num1 >= 5) {
        s[index++] = 'V';
        times = num1 - 5;
        for (; times > 0; --times) {
            s[index++] = 'I';
        }
        return ToRoman(0, s, index);
    } else if (num1 >= 4) {
        s[index++] = 'I';
        s[index++] = 'V';
        return ToRoman(num1 - 4, s, index);
    } else {
        times = num1;
        for (; times > 0; times--) {
            s[index++] = 'I';
        }
        s[index] = '\0';
        return;
    }
}

char* intToRoman(int num)
{
    char* s = (char*)malloc(20 * sizeof(char));
    memset(s, 0, 20);
    ToRoman(num, s, 0);
    return s;
}

int main(int argc, char** argv)
{
    printf("%s\n", intToRoman(atoi(argv[1])));
    return 0;
}