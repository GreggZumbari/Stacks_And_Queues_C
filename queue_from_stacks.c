/*
 * This is the file in which you'll write the functions required to implement
 * a queue using two stacks.  Make sure to add your name and @oregonstate.edu
 * email address below:
 *
 * Name: Greggory Hickman
 * Email: hickmang@oregonstate.edu
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stack.h"
#include "queue_from_stacks.h"

/*
 * This function should allocate and initialize all of the memory needed for
 * your queue and return a pointer to the queue structure.
 */
struct queue_from_stacks* queue_from_stacks_create() {
  //This is the queue that will be returned
  struct queue_from_stacks* queue = malloc(sizeof(struct queue_from_stacks));
  queue->s1 = stack_create();
  queue->s2 = stack_create();
  assert(queue);
  assert(queue->s1);
  assert(queue->s2);

  return queue;
}

/*
 * This function should free all of the memory allocated to a queue, including
 * the memory associated with each stack.
 *
 * Params:
 *   queue - the queue to be destroyed.  May not be NULL.  The function should
 *     exit the program with an error if queue is NULL.
 */
void queue_from_stacks_free(struct queue_from_stacks* queue) {
  assert(queue);

  //Dequeue everything in s1 and s2
  while (!stack_isempty(queue->s1)) {
    stack_pop(queue->s1);
  }
  while (!stack_isempty(queue->s2)) {
    stack_pop(queue->s2);
  }

  //Free the 2 stacks inside the struct, then the struct itself
  stack_free(queue->s1);
  stack_free(queue->s2);
  free(queue);
}

/*
 * This function should return 1 if a queue is completely empty or 0 if there
 * is at least one element stored in the queue.
 *
 * Params:
 *   queue - the queue whose emptiness is to be checked.  May not be NULL.
 *     The function should exit the program with an error if queue is NULL.
 *
 * Return:
 *   Should return 1 if the queue is empty or 0 otherwise.
 */
int queue_from_stacks_isempty(struct queue_from_stacks* queue) {
  assert(queue);
  //This one is simple enough that I don't think that an explanation is necessary
  if (stack_isempty(queue->s1) && stack_isempty(queue->s2)) {
    return 1;
  }
  else {
    return 0;
  }
}

/*
 * Should enqueue a new value onto the end of a queue.
 *
 * Params:
 *   queue - the queue onto which to enqueue a value.  May not be NULL.
 *     The function should exit the program with an error if queue is NULL.
 *   value - the new value to be enqueueed onto the queue
 */
void queue_from_stacks_enqueue(struct queue_from_stacks* queue, int value) {
  assert(queue);
  //Funnel all of s2 into s1. Now the list is upside-down.
  while(!stack_isempty(queue->s2)) {
    stack_push(queue->s1, stack_pop(queue->s2));
  }
  //Stick the new value into the now empty s2.
  stack_push(queue->s2, value);
  //Funnel all of s1 back into s2. Now the list is exactly how it was before, except now the new value is at the bottom of s2.
  while(!stack_isempty(queue->s1)) {
    stack_push(queue->s2, stack_pop(queue->s1));
  }
}

/*
 * Should return a queue's front value without removing that value from the
 * queue.
 *
 * Params:
 *   queue - the queue from which to read the front value.  May not be NULL or
 *     empty.  The function should exit the program with an error if queue is
 *     NULL or empty.
 *
 * Return:
 *   Should return the value stored at the front of the queue.
 */
int queue_from_stacks_front(struct queue_from_stacks* queue) {
  assert(queue);
  return stack_top(queue->s2);
}

/*
 * Should remove the front element from a queue and return its value.
 *
 * Params:
 *   queue - the queue from which to dequeue a value.  May not be NULL or
 *     empty.  The function should exit the program with an error if queue is
 *     NULL or empty.
 *
 * Return:
 *   Should return the value stored at the front of the queue before that value
 *   is dequeued.
 */
int queue_from_stacks_dequeue(struct queue_from_stacks* queue) {
  //Because of the way that I set up the enqueue, the oldest element will be on the top of the s2 stack
  return stack_pop(queue->s2);
}
