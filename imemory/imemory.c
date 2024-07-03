/**
 * @file imemory.h
 * @author SHUAIWEN CUI (cswoffice@163.com)
 * @brief This is the header file for the memory management module.
 * @version 1.0
 * @date 2024-06-30
 * @ref ALIENTEK memory.h & memory.c for STM32H7xx
 * @copyright Copyright (c) 2024
 *
 * ! NOTE:
 * ! The memory management is achieved by using linked lists.
 *
 */

#include "imemory.h"

#define SDRAM_START_ADDR 0xC0000000
#define SDRAM_SIZE 0x02000000  // 32MB

// block hearder structure: at the beginning of each block, size indicates the size of the block, next is the pointer to the next free block

typedef struct BlockHeader {
    size_t size;              // Block size including header
    struct BlockHeader* next; // Pointer to the next free block
} BlockHeader;

static BlockHeader* freeList = (BlockHeader*)SDRAM_START_ADDR;

void memory_init(void) {
    freeList->size = SDRAM_SIZE;
    freeList->next = NULL;
}

void* memory_alloc(size_t size) {
    BlockHeader* current = freeList;
    BlockHeader* previous = NULL;

    // Align size to the size of BlockHeader and to 32-bit boundary
    size = (size + sizeof(BlockHeader) + sizeof(uint32_t) - 1) & ~(sizeof(uint32_t) - 1);

    while (current) {
        if (current->size >= size) {
            if (current->size > size + sizeof(BlockHeader)) {
                // Split the block
                BlockHeader* newBlock = (BlockHeader*)((uint32_t*)current + size / sizeof(uint32_t));
                newBlock->size = current->size - size;
                newBlock->next = current->next;
                current->size = size;
                current->next = NULL;

                if (previous) {
                    previous->next = newBlock;
                } else {
                    freeList = newBlock;
                }
            } else {
                // Use the whole block
                if (previous) {
                    previous->next = current->next;
                } else {
                    freeList = current->next;
                }
            }
            return (void*)((uint32_t*)current + sizeof(BlockHeader) / sizeof(uint32_t));
        }

        previous = current;
        current = current->next;
    }

    // No suitable block found
    return NULL;
}

void memory_free(void* ptr) {
    if (!ptr) return;

    BlockHeader* block = (BlockHeader*)((uint32_t*)ptr - sizeof(BlockHeader) / sizeof(uint32_t));
    BlockHeader* current = freeList;
    BlockHeader* previous = NULL;

    while (current && current < block) {
        previous = current;
        current = current->next;
    }

    if (previous) {
        previous->next = block;
    } else {
        freeList = block;
    }
    block->next = current;

    // Merge adjacent blocks (optional, for reducing fragmentation)
    if ((uint32_t*)block + block->size / sizeof(uint32_t) == (uint32_t*)current) {
        block->size += current->size;
        block->next = current->next;
    }
    if (previous && (uint32_t*)previous + previous->size / sizeof(uint32_t) == (uint32_t*)block) {
        previous->size += block->size;
        previous->next = block->next;
    }
}
