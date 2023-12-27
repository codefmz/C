#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lengthOfLongestSubstring(char* s)
{
    if (s[0] == '\0') {
        return 0;
    }
    int offset[128];
    memset((void*)offset, -1, sizeof(offset));
    offset[s[0]] = 0;
    int len = 1, index = 0, i = 1, maxLen = 1;
    for (; s[i] != '\0'; i++) {
        int preIndex = offset[s[i]];
        offset[s[i]] = i;
        if (preIndex < index) {
            ++len;
        } else {
            maxLen = len > maxLen ? len : maxLen;
            len = i - preIndex;
            index = preIndex + 1;
        }
    }
    return maxLen > len ? maxLen : len;
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: ./test string\n");
        exit(-1);
    }

    printf("%d\n", lengthOfLongestSubstring(argv[1]));
    return 0;
}