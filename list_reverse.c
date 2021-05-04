/*
 * This is the file in which you'll write a function to reverse a linked list.
 * Make sure to add your name and @oregonstate.edu email address below:
 * 
 * Name: Greggory Hickman
 * Email: hickmang@oregonstate.edu
 */

#include <stdio.h>

#include "list_reverse.h"

/*
 * In this function, you will be passed a pointer to the first node of a singly-linked list.
 * You should reverse the linked list and return the new "first" pointer.  The reversal
 * must be done in place, and you may not allocate any new memory in this
 * function.
 *
 * Params:
 *   first - a pointer to the first node of a singly-linked list to be reversed
 *
 * Return:
 *   Should return the new first of the reversed list.  If first is NULL, this
 *   function should return NULL.
 */
struct node* list_reverse(struct node* first) {
  struct node* current = first;

  int length = 1;
  //Get the length of the list, 1st iteration through the list
  while (current->next != NULL) {
    current = current->next;
    length++;
  }

  current = first;
  int listValues[length];
  //Fill in listValues with the list's values, 2nd iteration
  for (int i = 0; current->next != NULL; i++) {
    listValues[i] = current->value;
    current = current->next;
  }

  current = first;
  //Reverse the list, 3rd iteration
  if (length > 1) {
    for (int i = 0; i < length - 1; i++) {
      current->value = listValues[length - i];
      printf("i: %d, val: %d\n", i, current->value);
      current = current->next;
    }
  }

  return current;
}
