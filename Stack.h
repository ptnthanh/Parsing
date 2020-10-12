/*
 * Stack.h
 *
 *  Created on: Oct 7, 2020
 *      Author: thanhpham
 */

#ifndef STACK_H_
#define STACK_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "LinkedList.h"

typedef struct Stack *Stack;
struct Stack;

extern Stack new_Stack();

extern bool Stack_isEmpty(Stack stack);

extern void Stack_push(Stack stack, char* data);

extern char* Stack_pop(Stack stack);

extern void Stack_free(Stack stack);

#endif /* STACK_H_ */
