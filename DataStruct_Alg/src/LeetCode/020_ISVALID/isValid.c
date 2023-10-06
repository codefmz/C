#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool isValid(char* s)
{
    int len = strlen(s) + 1;
    int i = 0, index = 0;
    char* st = (char*)malloc(sizeof(char) * len);

    for (; i < len; ++i) {
        switch (s[i]) {
        case '(':
        case '{':
        case '[': {
            s[index++] = s[i];
            break;
        }
        case ')': {
            if (index == 0 || s[--index] != '(') {
                free(st);
                return false;
            }
            break;
        }
        case '}': {
            if (index == 0 || s[--index] != '{') {
                free(st);
                return false;
            }
            break;
        }
        case ']': {
            if (index == 0 || s[--index] != '[') {
                free(st);
                return false;
            }
            break;
        }
        }
    }
    free(st);
    return index == 0;
}