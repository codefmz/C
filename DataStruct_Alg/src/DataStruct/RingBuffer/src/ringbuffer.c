#include "ringbuffer.h"
#include "log.h"
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum rbstate {
    RB_EMPTY = 0,
    RB_WRITE_MORE,
    RB_READ_MORE,
    RB_FULL,
    RB_BULT
} RB_STATUS;

void RingBufferInit(RingBuffer* rb, uint8_t* pool, uint16_t size)
{
    rb->readMirror = 0;
    rb->writeMirror = 0;

    rb->bufferPtr = pool;
    rb->bufferSize = size;
}

RB_STATUS RingBufferStatusGet(RingBuffer* rb)
{
    if (rb->readIndex == rb->writeIndex) {
        if (rb->readMirror == rb->writeMirror) {
            return RB_EMPTY;
        } else {
            return RB_FULL;
        }
    } else if (rb->readIndex < rb->writeIndex) {
        return RB_WRITE_MORE;
    } else {
        return RB_READ_MORE;
    }
    return RB_BULT;
}

uint16_t RingBufferWriteSpaceGet(RingBuffer* rb, RB_STATUS status)
{
    switch (status) {
    case RB_EMPTY:
        return rb->bufferSize;
    case RB_FULL:
        return 0;
    case RB_WRITE_MORE:
        return rb->bufferSize - rb->writeIndex + rb->readIndex;
    case RB_READ_MORE:
        return rb->readIndex - rb->writeIndex;
    default:
        break;
    }
    return 0;
}

uint16_t RingBufferReadSpaceGet(RingBuffer* rb, RB_STATUS status)
{
    switch (status) {
    case RB_EMPTY:
        return 0;
    case RB_FULL:
        return rb->bufferSize;
    case RB_READ_MORE:
        return rb->bufferSize - rb->readIndex + rb->writeIndex;
    case RB_WRITE_MORE:
        return rb->readIndex - rb->writeIndex;
    default:
        break;
    }
    return 0;
}

uint16_t RingBufferPut(RingBuffer* rb, uint8_t* ptr, uint16_t length)
{
    uint16_t size = 0;
    RB_STATUS status;

    status = RingBufferStatusGet(rb);
    size = RingBufferWriteSpaceGet(rb, status);

    if (size == 0) {
        LOG_INFO("write ring size = 0");
        return 0;
    }

    if (size < length) {
        LOG_ERROR("write ring size = %u is less then length = %u", size, length);
        return 0;
    }

    switch (status) {
    case RB_EMPTY:
    case RB_WRITE_MORE: { /* 写索引大于读索引 */
        if (rb->bufferSize - rb->writeIndex >= length) {
            memcpy(&rb->bufferPtr[rb->writeIndex], ptr, length);
            rb->writeIndex = (rb->writeIndex + length) & (rb->bufferSize - 1);
            if (rb->writeIndex == 0) {
                rb->writeMirror = !rb->writeMirror;
            }
            return length;
        }
        memcpy(&rb->bufferPtr[rb->writeIndex], ptr, rb->bufferSize - rb->writeIndex);
        memcpy(rb->bufferPtr, &ptr[rb->bufferSize - rb->writeIndex], length - rb->bufferSize + rb->writeIndex);
        rb->writeIndex = length - rb->bufferSize + rb->writeIndex;
        rb->writeMirror = !rb->writeMirror;
        break;
    }
    case RB_READ_MORE: {
        memcpy((void*)rb->bufferPtr, (void*)ptr, length);
        rb->writeIndex += length;
        break;
    }
    }
    return length;
}

uint16_t RingBufferGet(RingBuffer* rb, uint8_t* ptr, uint16_t length)
{
    uint16_t size = 0;
    RB_STATUS status;

    status = RingBufferStatusGet(rb);
    size = RingBufferReadSpaceGet(rb, status);

    if (size == 0) {
        LOG_INFO("read ring size = 0");
        return 0;
    }

    if (size < length) {
        LOG_ERROR("read ring size = %u is less then length = %u", size, length);
        return 0;
    }

    switch (status) {
    case RB_FULL:
    case RB_READ_MORE: { /* 读索引大于写索引 */
        if (rb->bufferSize - rb->readIndex >= length) {
            memcpy(ptr, &rb->bufferPtr[rb->readIndex], length);
            rb->readIndex = (rb->readIndex + length) & (rb->bufferSize - 1);
            if (rb->readIndex == 0) {
                rb->readMirror = !rb->readMirror;
            }
            return length;
        }
        memcpy(ptr, &rb->bufferPtr[rb->readIndex], rb->bufferSize - rb->readIndex);
        memcpy(&ptr[rb->bufferSize - rb->readIndex], rb->bufferPtr, length - rb->bufferSize + rb->readIndex);
        rb->readIndex = length - rb->bufferSize + rb->readIndex;
        rb->readMirror = !rb->readMirror;
        break;
    }
    case RB_WRITE_MORE: {
        memcpy(ptr, &rb->bufferPtr[rb->readIndex], length);
        rb->readIndex += length;
        break;
    }
    }
    return length;
}

#ifdef __cplusplus
}
#endif