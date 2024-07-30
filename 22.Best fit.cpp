#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MEMORY_SIZE 100
#define BLOCK_SIZE 10
typedef struct {
    int start;
    int size;
    int is_allocated;
} MemoryBlock;

void initialize_memory(MemoryBlock memory[], int num_blocks) {
    for (int i = 0; i < num_blocks; i++) {
        memory[i].start = i * BLOCK_SIZE;
        memory[i].size = BLOCK_SIZE;
        memory[i].is_allocated = 0;
    }
}

int allocate_memory(MemoryBlock memory[], int num_blocks, int request_size) {
    int num_blocks_needed = (request_size + BLOCK_SIZE - 1) / BLOCK_SIZE;

    int best_fit_index = -1;
    int min_size_diff = INT_MAX;
    int start_block = -1;
    int count = 0;

    for (int i = 0; i < num_blocks; i++) {
        if (memory[i].is_allocated == 0) {
            if (start_block == -1) {
                start_block = i;
            }
            count++;
            if (count == num_blocks_needed) {
                int total_size = (i - start_block + 1) * BLOCK_SIZE;
                int size_diff = total_size - request_size;
                if (size_diff < min_size_diff) {
                    min_size_diff = size_diff;
                    best_fit_index = start_block;
                }
                start_block = -1;
                count = 0;
            }
        } else {
            start_block = -1;
            count = 0;
        }
    }

    if (best_fit_index != -1) {
        for (int j = best_fit_index; j < best_fit_index + num_blocks_needed; j++) {
            memory[j].is_allocated = 1;
        }
        return memory[best_fit_index].start;
    }

    return -1;
}

void free_memory(MemoryBlock memory[], int num_blocks, int start_address) {
    int start_block = start_address / BLOCK_SIZE;

    for (int i = start_block; i < num_blocks && memory[i].start < start_address + BLOCK_SIZE; i++) {
        if (memory[i].start >= start_address) {
            memory[i].is_allocated = 0;
        }
    }
}

void print_memory(MemoryBlock memory[], int num_blocks) {
    printf("Memory Status:\n");
    for (int i = 0; i < num_blocks; i++) {
        printf("Block %d: Start = %d, Size = %d, %s\n",
               i, memory[i].start, memory[i].size,
               memory[i].is_allocated ? "Allocated" : "Free");
    }
}

int main() {
    int num_blocks = MEMORY_SIZE / BLOCK_SIZE;
    MemoryBlock memory[num_blocks];
    initialize_memory(memory, num_blocks);

    printf("Initial ");
    print_memory(memory, num_blocks);

    int request_size = 25;
    printf("\nAllocating %d bytes of memory...\n", request_size);
    int address = allocate_memory(memory, num_blocks, request_size);
    if (address != -1) {
        printf("Memory allocated at address %d\n", address);
    } else {
        printf("Failed to allocate memory\n");
    }

    print_memory(memory, num_blocks);

    printf("\nFreeing memory at address %d...\n", address);
    free_memory(memory, num_blocks, address);

    print_memory(memory, num_blocks);

    return 0;
}
