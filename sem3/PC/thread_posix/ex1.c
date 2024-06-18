#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 16

void *thread(void *thread_id) {
    int id = *((int *) thread_id);
    printf("Hello from thread %d\n", id);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int tab[NUM_THREADS]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

    for (int i = 0; i < NUM_THREADS; i++) {
        int code = pthread_create(&threads[i], NULL, thread, &tab[i]);
        if (code != 0) {
            fprintf(stderr, "pthread_create failed!\n");
            return EXIT_FAILURE;
        }
    }

    for (int i=0; i<NUM_THREADS; i++){
        if(pthread_join(threads[i], NULL)!=0){
            fprintf(stderr, "pthread_join failed!\n");
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}