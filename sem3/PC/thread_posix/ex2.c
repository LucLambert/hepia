#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

static int sum=0;
static int* tab;
static int size;

void *thread(void __attribute__((unused)) *arg){
    for(int i=0; i<size; i++){
        sum+=tab[i];
    }
    return NULL;
}

int main(int argc, char** argv) {
    size=argc-1;
    tab=(int*)malloc(size*sizeof(int));

    for(int i=1; i<argc; i++){
        tab[i-1]=atoi(argv[i]);
    }

    pthread_t thread_one;
    if(pthread_create(&thread_one, NULL, thread, NULL) != 0){
        fprintf(stderr,"failed to create thread\n");
        return EXIT_FAILURE;
    }
    if(pthread_join(thread_one, NULL)!=0){
        fprintf(stderr, "pthread_join failed!\n");
        return EXIT_FAILURE;
    }
    printf(" = %d\n",sum);

    free(tab);

    return EXIT_SUCCESS;
}