#include "stack.h"
#include "util.h"
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

int main(int argc, char** argv)
{
    printf(" size of Stack = %d\r\n", sizeof(Stack));
    Test_Stack_001();
}