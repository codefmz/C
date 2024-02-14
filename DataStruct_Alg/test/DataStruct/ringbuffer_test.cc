#include "log.h"
#include "ringbuffer.h"
#include <gtest/gtest.h>
#include <string.h>

typedef struct message {
    uint16_t len;
    char data[];
} Message;

TEST(ringbuffer, test122)
{
    RingBuffer rb = { 0 };
    uint8_t* pool = (uint8_t*)malloc(128 * sizeof(uint8_t));
    const char* str1 = "hello5555555555555555555555555555555544444444444444444444";
    const char* str2 = "20246666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666";
    uint8_t buffer[256] = { 0 };
    Message *mes1, *mes2;
    uint16_t len1, len2;
    Message *rMes1, *rMes2;

    mes1 = (Message*)malloc(sizeof(Message) + strlen(str1) + 1);
    memset(mes1, 0, sizeof(Message) + strlen(str1) + 1);
    mes1->len = strlen(str1) + 1;
    strncpy(mes1->data, str1, mes1->len);

    mes2 = (Message*)malloc(sizeof(Message) + strlen(str2) + 1);
    memset(mes2, 0, sizeof(Message) + strlen(str2) + 1);
    mes2->len = strlen(str2) + 1;
    strncpy(mes2->data, str2, mes2->len);

    RingBufferInit(&rb, pool, 128);
    RingBufferPut(&rb, (uint8_t*)mes1, sizeof(Message) + strlen(str1) + 1);

    RingBufferGet(&rb, (uint8_t*)&len1, sizeof(uint16_t));
    rMes1 = (Message*)malloc(sizeof(Message) + len1 * sizeof(uint8_t));
    RingBufferGet(&rb, (uint8_t*)rMes1->data, len1 * sizeof(uint8_t));
    EXPECT_STREQ(rMes1->data, str1);

    RingBufferPut(&rb, (uint8_t*)mes2, sizeof(Message) + strlen(str2) + 1);

    RingBufferGet(&rb, (uint8_t*)&len2, sizeof(uint16_t));
    rMes2 = (Message*)malloc(sizeof(Message) + len2 * sizeof(uint8_t));
    RingBufferGet(&rb, (uint8_t*)rMes2->data, len2 * sizeof(uint8_t));
    EXPECT_STREQ(rMes2->data, str2);

    free(mes1);
    free(mes2);
    free(rMes1);
    free(rMes2);
}