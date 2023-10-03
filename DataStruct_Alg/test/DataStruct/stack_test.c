#include "stack.h"
#include "util.h"
#include <ctype.h>
void Test_Stack_001()
{
    Stack st;
    CreateStack(&st, 10, sizeof(int));
    int temp = 1;
    Push(&temp, &st);
    printf(" stack size = %d\n", st.topOfStack);
    temp = 2;
    Push(&temp, &st);
    temp = 3;
    Push(&temp, &st);
    ASSERT_EQUAL(*(int*)Top(&st), 3);
    temp = 4;
    Push(&temp, &st);
    ASSERT_EQUAL(*(int*)Top(&st), 4);
    temp = 5;
    Push(&temp, &st);
    ASSERT_EQUAL(*(int*)Top(&st), 5);
    temp = 6;
    Push(&temp, &st);
    ASSERT_EQUAL(*(int*)Top(&st), 6);
    printf(" stack size = %d\n", st.topOfStack);
    printf(" stack value: \t");
    void* elem = NULL;
    while (st.topOfStack != 0) {
        Pop(&elem, &st);
        printf("%d --> ", *(int*)elem);
        free(elem);
        elem = NULL;
    }
    printf("\n");
    MakeEmpty(&st);
}

int GetPriority(char c)
{
    switch (c) {
    case '(':
        return 3;
    case '*':
    case '/':
        return 2;
    case '+':
    case '-':
        return 1;
    }
}

/**
 *中缀表达式修改为后缀表达式
 */
void InfixToPostfix(const char* infix, char* postfix)
{
    Stack oper;
    uint32_t len;
    uint32_t i = 0;
    uint32_t index = 0;
    void* topChar = NULL;
    3 + 4 * 5 + (5 * 4 + 6) * 9; // 345*+54*6+9*+;
    len = strlen(infix);
    CreateStack(&oper, len, sizeof(char));
    for (; infix[i] != '\0'; ++i) {
        if (isdigit(infix[i])) {
            postfix[index++] = infix[i];
        } else if (isspace(infix[i])) {
            continue;
        } else if (oper.topOfStack == 0 || *(char*)Top(&oper) == '(') {
            Push((void*)(infix + i), &oper);
        } else if (infix[i] != ')') {
            int topPri = GetPriority(*(char*)Top(&oper));
            int curPri = GetPriority(infix[i]);
            while (curPri <= topPri && *(char*)Top(&oper) != '(') {
                Pop(&topChar, &oper);
                postfix[index++] = *(char*)topChar;
                free(topChar);
                if (oper.topOfStack > 0) {
                    topPri = GetPriority(*(char*)Top(&oper));
                } else {
                    topPri = -1;
                }
            }
            Push((void*)(infix + i), &oper);
        } else if (infix[i] == ')') {
            Pop(&topChar, &oper);
            while (*(char*)topChar != '(') {
                postfix[index++] = *(char*)topChar;
                free(topChar);
                topChar = NULL;
                Pop(&topChar, &oper);
            }
        }
    }
    while (oper.topOfStack != 0) {
        Pop(&topChar, &oper);
        postfix[index++] = *(char*)topChar;
        free(topChar);
        topChar = NULL;
    }
    postfix[index] = '\0';
    MakeEmpty(&oper);
}

void Test_InfixToPostfix_001()
{
    const char* infix = "3 + 4 * 5 + (5 * 4 + 6) * 9";
    char* postfix = (char*)malloc(strlen(infix) + 1);
    InfixToPostfix(infix, postfix);
    printf("postfix = %s\r\n", postfix);
    ASSERT_EQUAL_STR(postfix, "345*+54*6+9*+");
}

int Polish(const char* infix)
{
    Stack st;
    uint32_t i = 0;
    int res = 0;
    int len = strlen(infix) + 1;
    char* postfix;
    void *num1 = NULL, *num2 = NULL;
    int tempRes = 0;

    postfix = (char*)malloc(len);
    memset(postfix, 0, len);
    InfixToPostfix(infix, postfix);
    printf("postfix = %s\r\n", postfix);
    CreateStack(&st, len, sizeof(int));

    for (; postfix[i] != '\0'; ++i) {
        if (isdigit(postfix[i])) {
            tempRes = postfix[i] - '0';
            Push((void*)(&tempRes), &st);
        } else {
            Pop(&num1, &st);
            Pop(&num2, &st);
            switch (postfix[i]) {
            case '*': {
                tempRes = (*(int*)num2) * (*(int*)num1);
                Push((void*)&tempRes, &st);
                break;
            }
            case '/': {
                tempRes = (*(int*)num2) / (*(int*)num1);
                Push((void*)&tempRes, &st);
                break;
            }
            case '+': {
                tempRes = (*(int*)num2) + (*(int*)num1);
                Push((void*)&tempRes, &st);
                break;
            }
            case '-': {
                tempRes = (*(int*)num2) - (*(int*)num1);
                Push((void*)&tempRes, &st);
                break;
            }
            default:
                break;
            }
            free(num1);
            free(num2);
            num1 = NULL;
            num2 = NULL;
        }
    }
    Pop(&num1, &st);
    res = *(int*)(num1);
    free(num1);
    num1 = NULL;
    printf("res = %d\r\n", res);
    MakeEmpty(&st);
    return res;
}

void Test_Postfix_001()
{
    int res = Polish("3 + 4 * 5 + (5 * 4 + 6) * 9");
    ASSERT_EQUAL(res, 257);
    res = Polish("3 + 4 * 5 + (5 * 7 - 6) * 9");
    ASSERT_EQUAL(res, 284);
    res = Polish("(3 + 4) * 5 + (5 * 7 - 6) * 9 - 8 / 4");
    ASSERT_EQUAL(res, 296);
}

int main(int argc, char** argv)
{
    // printf(" size of Stack = %d\r\n", sizeof(Stack));
    // Test_Stack_001();
    // Test_InfixToPostfix_001();
    Test_Postfix_001();
}