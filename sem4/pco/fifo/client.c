#include "fifo.h"
#include <stdio.h>

int main(){
    init_fifo(10);
    push_fifo("Hello ! ", 9);
    printf("sending msg\n");
    destroy_fifo();
    return 0;
}