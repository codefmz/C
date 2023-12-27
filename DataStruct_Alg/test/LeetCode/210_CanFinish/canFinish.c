#include <stdbool.h>
#include <stdlib.h>

bool canFinish(int numCourses, int** prerequisites, int prerequisitesSize, int* prerequisitesColSize)
{
    // 很久之前写的，当初只会C，用的是建图的方法，跑得很慢，贴出来不做注释了
    int n = numCourses, m = prerequisitesSize;
    int* intake = (int*)malloc(sizeof(int) * n);
    if (intake == NULL)
        return NULL;
    bool** matrix = (bool**)malloc(sizeof(bool*) * n);
    if (matrix == NULL)
        return NULL;
    for (int i = 0; i < n; i++) {
        intake[i] = 0;
        matrix[i] = (bool*)malloc(sizeof(bool) * n);
        if (matrix[i] == NULL)
            return NULL;
        for (int j = 0; j < n; j++) {
            matrix[i][j] = false;
        }
    }
    for (int i = 0; i < m; i++) {
        int a = prerequisites[i][1], b = prerequisites[i][0];
        intake[b]++;
        matrix[a][b] = true;
    }
    int queue[100000];
    int num = n;
    while (num > 0) {
        int front = 0, rear = -1;
        for (int i = 0; i < n; i++) {
            if (intake[i] == 0) {
                intake[i] = -1;
                queue[++rear] = i;
                num--;
            }
        }
        if (rear == -1 && num > 0)
            return false;
        for (int index = rear; front <= index; front++) {
            for (int i = 0; i < n; i++) {
                if (matrix[queue[front]][i]) {
                    matrix[queue[front]][i] = false;
                    intake[i]--;
                }
            }
        }
    }
    return true;
}