#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* longestPalindrome(char* s)
{

    if (s == NULL) {
        return NULL;
    }

    if (s == NULL) {
        return NULL;
    }
    int len = strlen(s);
    int** p = (int**)malloc(len * sizeof(int*)); /* p[i][j] i 到 j 是否满足回文字符串 */
    for (int i = 0; i < len; i++) {
        p[i] = malloc(len * sizeof(int));
        memset(p[i], 0, len);
        p[i][i] = 1;
    }

    int index = 0, maxLen = 1;
    for (int COL = 0; COL < len; ++COL) {
        for (int ROW = 0; ROW < len; ++ROW) {
            if (ROW <= COL - 1) {
                if (ROW <= COL - 2) {
                    p[ROW][COL] = p[ROW + 1][COL - 1] && s[ROW] == s[COL];
                } else {
                    p[ROW][COL] = s[ROW] == s[COL];
                }
                if (p[ROW][COL] && maxLen < COL - ROW + 1) {
                    maxLen = COL - ROW + 1;
                    index = ROW;
                }
            }
        }
    }
    char* res = malloc(maxLen + 1);
    memset(res, 0, maxLen + 1);
    res = strncpy(res, s + index, maxLen);
    res[maxLen] = '\0';
    for (int i = 0; i < len; i++) {
        free(p[i]);
    }
    return res;
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: ./test string\n");
        exit(-1);
    }
    printf("%s\n", longestPalindrome(argv[1]));
    return 0;
}
