#ifndef _UTIL_RADIX_TREE_H_
#define _UTIL_RADIX_TREE_H_

#include <stdint.h>

#define MASK32 0xFFFFFFFF
#define MASK64 0xFFFFFFFFFFFFFFFF

void* util_radix_tree_create(int preallocate);

void util_radix_tree_destroy(void* vtree);

int util_radix32tree_insert(void* vtree, uint32_t key, uint32_t mask, uintptr_t value);

int util_radix32tree_delete(void* vtree, uint32_t key, uint32_t mask);

uintptr_t util_radix32tree_find(void* vtree, uint32_t key);

int util_radix64tree_insert(void* vtree, uint64_t key, uint64_t mask, uintptr_t value);

int util_radix64tree_delete(void* vtree, uint64_t key, uint64_t mask);

uintptr_t util_radix64tree_find(void* vtree, uint64_t key);

int util_radix128tree_insert(void* vtree, uint8_t* key, uint8_t* mask, uintptr_t value);

int util_radix128tree_delete(void* vtree, uint8_t* key, uint8_t* mask);

uintptr_t util_radix128tree_find(void* vtree, uint8_t* key);

#endif // _UTIL_RADIX_TREE_H_