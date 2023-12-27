#include <stdlib.h>
#include <string.h>

int longestValidParentheses(char* s)
{
    int len;
    int i;
    int* dp = NULL;
    int maxLen = 0;

    len = strlen(s);
    if (len == 0) {
        return 0;
    }

    dp = (int*)malloc(sizeof(int) * len);
    memset(dp, 0, sizeof(int) * len);
    for (i = 1; s[i] != '\0'; ++i) {
        if (s[i] == '(') {
            dp[i] == 0;
            continue;
        }

        if (i - dp[i - 1] - 1 >= 0) {
            continue;
        }

        if (s[i - dp[i - 1] - 1] == '(') {
            if (i - dp[i - 1] - 2 > 0) {
                dp[i] = dp[i - 1] + dp[i - dp[i - 1] - 2] + 2;
            } else {
                dp[i] = dp[i - 1] + 2;
            }
            maxLen = dp[i] > maxLen ? dp[i] : maxLen;
        }
    }

    free(dp);
    return maxLen;
}