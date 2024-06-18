#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "fifo.h"

void* task_client(){
    char c[3];
    for (uint8_t i=1; i<16; i++) {
        c[1] = (char)(i%10+48);
        c[0] = i >= 10 ? 49 : 48;
        c[2] = '\0';
        push_fifo(c, 3);
    }
    return NULL;
}

void* task_server(){
    for (int i=0; i<15; i++) {
        char c[30];
        get_fifo(c, 30);
        printf("%s\n",c);
        usleep(200000);
    }
    return NULL;
}

int main(){
    init_fifo(7);

    pthread_t client;
    pthread_t server;
    if(pthread_create(&client, NULL, task_client, NULL) != 0)
        fprintf(stderr, "cannot create thread client\n");
    if(pthread_create(&server, NULL, task_server, NULL) != 0)
        fprintf(stderr, "cannot create thread server\n");
    if (pthread_join(client,NULL)!=0) {
        fprintf(stderr, "cannot join thread client\n");
    }
    if (pthread_join(server,NULL)!=0) {
        fprintf(stderr, "cannot join thread server\n");
    }
    return EXIT_SUCCESS;
}