#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct argument {
    char** args;
    int nbr;
} argument_t;

void *thread(void *arg){
    static int res=0;
    argument_t* a = (argument_t*)arg;
    for(int i=0; i<a->nbr;i++){
        res+=atoi(a->args[i]);
    }
    return &res;
}

int main(int argc, char** argv) {

    pthread_t thread_one;
    argument_t args = {argv, argc};
    if(pthread_create(&thread_one, NULL, thread, &args) != 0){
        fprintf(stderr,"failed to create thread\n");
        return EXIT_FAILURE;
    }
    int* sum;
    if(pthread_join(thread_one, (void**)&sum)!=0){
        fprintf(stderr, "pthread_join failed!\n");
        return EXIT_FAILURE;
    }
    printf(" = %d\n",*sum);

    return EXIT_SUCCESS;
}