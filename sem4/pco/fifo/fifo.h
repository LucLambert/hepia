#ifndef _FIFO_H
    #define _FIFO_H
    #include <mqueue.h>
    #include "string.h"

    void init_fifo(int maxmsg);
    void push_fifo(char* str, int size);
    void get_fifo(char str[], int len);
    void destroy_fifo();

#endif