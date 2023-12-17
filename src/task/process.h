#ifndef PROCESS_H
#define PROCESS_H

#include <stdbool.h>
#include <stdint.h>
#include "task.h"
#include "../config.h"
#include "../loader/formats/elfloader.h"

#define PROCESS_FILE_TYPE_ELF    0
#define PROCESS_FILE_TYPE_BIN    1

typedef unsigned char PROCESS_FILE_TYPE;

struct process_allocation{
    void* ptr;
    size_t size;
};

struct process{
    uint16_t pid;
    char filename[BOIOS_MAX_PATH];
    // main process task
    struct task* task;
    // keep track of allocations memory so it can be freed later
    struct process_allocation allocations[BOIOS_MAX_PROGRAM_ALLOCATIONS];
    
    PROCESS_FILE_TYPE filetype;

    // physical pointer to process memory
    union{
        void* ptr;
        struct elf_file* elf_file;
    };
    // phyiscal pointer to stack memory
    void* stack;
    // size of data pointed to by ptr
    uint32_t size;

    struct keyboard_buffer{
        char buffer[BOIOS_KEYBOARD_BUFFER_SIZE];
        int tail;
        int head; 
    } keyboard;
};

int process_load_for_slot(const char* filename, struct process** process, int process_slot);
int process_load(const char* filename, struct process** process);
int process_load_switch(const char* filename, struct process** process);
int process_switch(struct process* process);
struct process* process_current(void);
struct process* process_get(int pid);
void* process_malloc(struct process* process, size_t size);
void process_free(struct process* process, void* ptr);

#endif