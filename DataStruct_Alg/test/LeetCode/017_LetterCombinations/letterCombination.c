#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char** letterCombinations(char* digits, int* returnSize)
{
    int total = 1, len = 0, i = 0, den = 0, k = 0;
    const char* letter[8] = { "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };
    int num[8] = { 3, 3, 3, 3, 3, 4, 3, 4 };
    char** res = NULL;

    len = strlen(digits);
    if (len == 0) {
        return NULL;
    }

    for (; i < len; i++) {
        total *= num[digits[i] - '0' - 2];
    }

    den = total;
    *returnSize = total;
    res = (char**)malloc(total * sizeof(char*));
    memset(res, 0, sizeof(char*) * total);
    for (i = 0; i < total; i++) {
        res[i] = (char*)malloc((len + 1) * sizeof(char));
        memset(res[i], 0, (len + 1) * sizeof(char));
        res[i][len] = '\0';
    }

    int col = 0, row = 0;
    for (i = 0; i < len; i++) {
        int index = digits[i] - '0' - 2;
        den = den / num[index];
        for (k = 0; k < total; k++) {
            row = k / den % num[index];
            res[k][col] = letter[index][row];
        }
        ++col;
    }
    return res;
}

int main(int argc, char** argv)
{
    int i, size = 0;
    char** letters = letterCombinations(argv[1], &size);
    for (i = 0; i < size; i++) {
        printf("%s\n", letters[i]);
        free(letters[i]);
    }
    free(letters);
    return 0;
}