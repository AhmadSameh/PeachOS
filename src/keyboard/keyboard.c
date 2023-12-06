#include "keyboard.h"
#include "../status.h"
#include "../task/process.h"
#include "../task/task.h"

static struct keyboard* keyboard_list_head = 0;
static struct keyboard* keyboard_list_tail = 0;

static int keyboard_get_tail_index(struct process* process);

void keyboard_init(){

}

int keyboard_insert(struct keyboard* keyboard){
    int res = 0;
    if(keyboard->init == 0){
        res = -EINVARG;
        goto out;
    }
    if(keyboard_list_tail){
        keyboard_list_tail->next = keyboard;
        keyboard_list_tail = keyboard; 
    }else{
        keyboard_list_head = keyboard;
        keyboard_list_tail = keyboard;
    }
    res = keyboard->init();
out:
    return res;
}

void keyboard_push(char c){
    struct process* process = process_current();
    if(process == 0)
        return;
    int real_index = keyboard_get_tail_index(process);
    process->keyboard.buffer[real_index] = c;
    process->keyboard.tail++;
}

char keyboard_pop(){
    if(task_current() == 0)
        return 0;
    struct process* process = task_current()->process;
    int real_index = process->keyboard.head % sizeof(process->keyboard.buffer);
    char c = process->keyboard.buffer[real_index];
    if(c == 0)
        return 0;
    process->keyboard.buffer[real_index] = 0;
    process->keyboard.head++;
    return c;
}

void keyboard_backspace(struct process* process){
    process->keyboard.tail--;
    int real_index = keyboard_get_tail_index(process);
    process->keyboard.buffer[real_index] = 0x00;
}

static int keyboard_get_tail_index(struct process* process){
    return process->keyboard.tail % sizeof(process->keyboard.buffer);
}
