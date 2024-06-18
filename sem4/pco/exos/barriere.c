#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct barrier {
  int nbr;
  int cpt;
} barrier_t;

barrier_t b;

void barrier_init(barrier_t *b, int count) {
  b->nbr = count;
  b->cpt = 0;
}

void barrier_wait(barrier_t *b) {
  b->cpt++;
  while (b->nbr > b->cpt);
}

void barrier_destroy(barrier_t *b) {
  b->nbr = 0;
  b->cpt = 0;
}

void func() {
  printf("2nd thread before barrier\n");
  barrier_wait(&b);
  printf("2nd thread after barrier \n");
}

int main() {
  printf("main thread started\n");
  barrier_init(&b, 2);
  pthread_t thread;
  pthread_create(&thread, NULL, (void*)func, NULL);
  barrier_wait(&b);
  printf("main thread finished\n");
  pthread_join(thread, NULL);
  barrier_destroy(&b);
  return EXIT_SUCCESS;
  return 0;
}