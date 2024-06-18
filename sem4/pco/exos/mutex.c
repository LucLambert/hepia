#include "thread_wrapper.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG

#define STACK_SIZE 100000
#define THREAD_COUNT 100
#define NB_OF_PUSH_POP 1000

typedef struct {
  int* top;
  int size;
} stack_t;

typedef struct {
  int id;
  stack_t *stack;
} thr_params;

bool stack_create(stack_t *s, int max_size) { 
	s->top = malloc(max_size*sizeof(int));
	s->size=max_size;
	s->top=&(s->top[0]);
	return 0;
}

void stack_destroy(stack_t *s) {}

void stack_push(stack_t *s, int val) {
	*++(s->top)=val;
}

int stack_pop(stack_t *s) { 
	return *--(s->top);
}

bool stack_is_empty(stack_t *s) { return 0; }

void *test_stack(void *data) {
  thr_params *p = (thr_params *)data;

  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  unsigned int seed = (unsigned int)ts.tv_nsec;

  for (int i = 0; i < NB_OF_PUSH_POP; i++) {
    // push
    int val = rand_r(&seed) % 1000;
    stack_push(p->stack, val);

    // pop
    if (!stack_is_empty(p->stack)) {
      stack_pop(p->stack);
    }
  }
  return NULL;
}

int main() {
  stack_t s;
  if (!stack_create(&s, STACK_SIZE)) {
    fprintf(stderr, "Failed creating stack!\n");
    return EXIT_FAILURE;
  }
#ifdef DEBUG
  printf("Created stack of %d\n", STACK_SIZE);
#endif

#ifdef DEBUG
  printf("Launching %d threads\n", THREAD_COUNT);
#endif
  pthread_t t[THREAD_COUNT];
  thr_params p[THREAD_COUNT];
  for (int i = 0; i < THREAD_COUNT; i++) {
    p[i].id = i;
    p[i].stack = &s;
    thread_create(&t[i], test_stack, &p[i]);
  }

  for (int i = 0; i < THREAD_COUNT; i++)
    thread_join(t[i], NULL);

#ifdef DEBUG
  printf("Stack empty ? %s\n", stack_is_empty(&s) ? "yes" : "NO!");
#endif

  stack_destroy(&s);
#ifdef DEBUG
  printf("Stack destroyed\n");
#endif

  return EXIT_SUCCESS;
}