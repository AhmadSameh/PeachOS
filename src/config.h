#ifndef CONFIG_H
#define CONFIG_H

#define KERNEL_CODE_SELECTOR    0x08
#define KERNEL_DATA_SELECTOR    0x10

#define BOIOS_TOTAL_INTERRUPTS  512

// heap defines
#define BOIOS_HEAP_SIZE_BYTES   104857600 // 100 megabytes of heap
#define BOIOS_HEAP_BLOCK_SIZE   4096 // block size in bytes
#define BOIOS_HEAP_ADDRESS      0x01000000 // starting address of heap data pool
#define BOIOS_HEAP_TABLE_ADDRESS 0x00007E00 // starting address of heap table

#define BOIOS_SECTOR_SIZE 512

#define BOIOS_MAX_FILESYSTEMS       12
#define BOIOS_MAX_FILE_DESCRIPTORS  512

#define BOIOS_MAX_PATH  128

#endif