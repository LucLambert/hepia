#include <stdbool.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Cette fonction initialise le verrou passé en argument
void init_lock(bool *lock_ptr) {
// A remplir
    *lock_ptr=false;
}
// Cette fonction verrouille (acquiert) le verrou passé en argument
void acquire_lock(bool *lock_ptr) {
// A remplir
    while (__sync_val_compare_and_swap(lock_ptr,0,1));
}
// Cette fonction déverrouille (relâche) le verrou passé en argument
void release_lock(bool *lock_ptr) {
// A remplir
    *lock_ptr=false;
}

bool enter[2] = { false, false };
int turn = 0;
int cpt = 0;

void T0(){
    enter[0] = true;
    turn = 1;
    while (enter[1] && turn == 1) {}
    for (int i=0; i<1000000; i++) {
        cpt++;
    }
    enter[0] = false;
}

void T1(){
    enter[1] = true;
    turn = 0;
    while (enter[0] && turn == 0) {}
    for (int i=0; i<1000000; i++) {
        cpt++;
    }
    enter[1] = false;
}

int main(){
    pthread_t th[2];
    if (pthread_create(&th[0], NULL, (void*)T0, NULL) != 0)
        fprintf(stderr, "can't create thread\n");
    if (pthread_create(&th[1], NULL, (void*)T1, NULL) != 0)
        fprintf(stderr, "can't create thread\n");

    if(pthread_join(th[0], NULL)!=0)
        fprintf(stderr, "can't join thread\n");
    if(pthread_join(th[1], NULL)!=0)
        fprintf(stderr, "can't join thread\n");

    printf("%d\n",cpt);
    return 0;
}