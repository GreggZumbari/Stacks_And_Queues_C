/*
 * This is the file in which you'll write the functions required to implement
 * a stack using two queues.  Make sure to add your name and @oregonstate.edu
 * email address below:
 *
 * Name: Greggory Hickman
 * Email: hickmang@oregonstate.edu
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "queue.h"
#include "stack_from_queues.h"

/*
 * This function should allocate and initialize all of the memory needed for
 * your stack and return a pointer to the stack structure.
 */
struct stack_from_queues* stack_from_queues_create() {
  //This is the stack that will be returned
  struct stack_from_queues* stack = malloc(sizeof(struct stack_from_queues));
  stack->q1 = queue_create();
  stack->q2 = queue_create();
  assert(stack);
  assert(stack->q1);
  assert(stack->q2);

  return stack;
}

/*
 * This function should free all of the memory allocated to a stack, including
 * the memory associated with each queue.
 *
 * Params:
 *   stack - the stack to be destroyed.  May not be NULL.  The function should
 *     exit the program with an error if stack is NULL.
 */
void stack_from_queues_free(struct stack_from_queues* stack) {
  assert(stack);

  //Pop everything in q1 and q2
  while (!queue_isempty(stack->q1)) {
    queue_dequeue(stack->q1);
  }
  while (!queue_isempty(stack->q2)) {
    queue_dequeue(stack->q2);
  }

  //Free the 2 stacks inside the struct, then the struct itself
  queue_free(stack->q1);
  queue_free(stack->q2);
  free(stack);
}

/*
 * This function should return 1 if a stack is completely empty or 0 if there
 * is at least one element stored in the stack.
 *
 * Params:
 *   stack - the stack whose emptiness is to be checked.  May not be NULL.
 *     The function should exit the program with an error if stack is NULL.
 *
 * Return:
 *   Should return 1 if the stack is empty or 0 otherwise.
 */
int stack_from_queues_isempty(struct stack_from_queues* stack) {
  assert(stack);
  if (queue_isempty(stack->q1) && queue_isempty(stack->q2)) {
    return 1;
  }
  else {
    return 0;
  }
}

/*
 * Should push a new value onto a stack.
 *
 * Params:
 *   stack - the stack onto which to push a value.  May not be NULL.
 *     The function should exit the program with an error if stack is NULL.
 *   value - the new value to be pushed onto the stack
 */
void stack_from_queues_push(struct stack_from_queues* stack, int value) {
  assert(stack);
  //Funnel all of s2 into s1. Now the list is upside-down.
  while(!queue_isempty(stack->q2)) {
    queue_enqueue(stack->q1, queue_dequeue(stack->q2));
  }
  //Stick the new value into the now empty s2.
  queue_enqueue(stack->q2, value);
  //Funnel all of s1 back into s2. Now the list is exactly how it was before, except now the new value is at the bottom of s2.
  while(!queue_isempty(stack->q1)) {
    queue_enqueue(stack->q2, queue_dequeue(stack->q1));
  }
}

/*
 * Should return a stack's top value without removing that value from the
 * stack.
 *
 * Params:
 *   stack - the stack from which to read the top value.  May not be NULL or
 *     empty.  The function should exit the program with an error if stack is
 *     NULL or empty.
 *
 * Return:
 *   Should return the value stored at the top of the stack.
 */
int stack_from_queues_top(struct stack_from_queues* stack) {
  assert(stack);
  return queue_front(stack->q2);
}

/*
 * Should remove the top element from a stack and return its value.
 *
 * Params:
 *   stack - the stack from which to pop a value.  May not be NULL or
 *     empty.  The function should exit the program with an error if stack is
 *     NULL or empty.
 *
 * Return:
 *   Should return the value stored at the top of the stack before that value
 *   is popped.
 */
int stack_from_queues_pop(struct stack_from_queues* stack) {
  return queue_dequeue(stack->q2);
}
