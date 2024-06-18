#include "fifo.h"
#include <stdio.h>

int main(){
    init_fifo(10);
    char buff[1000];
    get_fifo(buff, 1000);
    printf("%s\n",buff);
    destroy_fifo();
}