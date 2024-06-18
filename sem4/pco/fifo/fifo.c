#include "fifo.h"

static mqd_t message;

void init_fifo(int maxmsg){
    struct mq_attr attr; // queue attributes
    attr.mq_maxmsg = maxmsg;
    attr.mq_msgsize = 30;
    attr.mq_flags = attr.mq_curmsgs= 0;

    message = mq_open ("/my_message", O_RDWR | O_CREAT,
    0664, &attr);
}

void push_fifo(char* str, int size){
    unsigned int prio=1;
    mq_send(message, str,
        size, prio);
}

void get_fifo(char str[], int len){
    unsigned int prio;
    mq_receive(message, str,
    len, &prio);
}

void destroy_fifo(){
    mq_close(message);
}