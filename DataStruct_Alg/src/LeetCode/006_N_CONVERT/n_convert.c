#include "stdio.h"
#include "stdlib.h"
#include "string.h"

char* convert(char* s, int numRows)
{
    int len = 0, num = 0, i = 0, col = 0;
    int rem = 0, index = 0;
    char* res;

    if (numRows == 1) {
        return s;
    }

    num = numRows - 2 + numRows;
    len = strlen(s);
    col = len / num * (numRows - 1);
    rem = len % num;
    res = malloc(sizeof(char) * len + 1);

    if (rem > numRows) {
        col = col + 1 + rem - numRows;
    } else if (rem > 0) {
        ++col;
    }

    char** graph = malloc(sizeof(char*) * numRows);
    for (i = 0; i < numRows; i++) {
        graph[i] = malloc(sizeof(char) * col);
        memset(graph[i], '\0', col);
    }

    for (i = 0; i < len; ++i) {
        if ((i - index * num) / numRows == 0) {
            graph[i - index * num][index * (numRows - 1)] = s[i];
        } else {
            graph[numRows - (i - numRows - index * num + 2)][index * (numRows - 1) + i - numRows - index * num + 1] = s[i];
        }
        if (i - index * num == num - 1) {
            ++index;
        }
    }

    index = 0;
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < col; ++j) {
            if (graph[i][j] != '\0') {
                res[index++] = graph[i][j];
            }
        }
    }
    res[index] = '\0';

    for (i = 0; i < numRows; i++) {
        free(graph[i]);
    }

    return res;
}

int main(int argc, char** argv)
{
    if (argc < 3) {
        fprintf(stderr, "./test string num\n");
        exit(-1);
    }

    printf("%s\n", convert(argv[1], atoi(argv[2])));
    return 0;
}
