#ifndef __RINGBUFFER_H__
#define __RINGBUFFER_H__

#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ringbuffer {
    uint8_t* bufferPtr;
    uint16_t readMirror : 1;
    uint16_t readIndex : 15;
    uint16_t writeMirror : 1;
    uint16_t writeIndex : 15;
    uint16_t bufferSize;
} RingBuffer;

void RingBufferInit(RingBuffer* rb, uint8_t* pool, uint16_t size);

uint16_t RingBufferPut(RingBuffer* rb, uint8_t* ptr, uint16_t length);

uint16_t RingBufferGet(RingBuffer* rb, uint8_t* ptr, uint16_t length);

#ifdef __cplusplus
}
#endif

#endif //__RINGBUFFER_H__