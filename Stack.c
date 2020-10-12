/*
 * Stack.c
 *
 *  Created on: Oct 7, 2020
 *      Author: thanhpham
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Stack.h"
#include "LinkedList.h"

struct Stack{
    LinkedList list;
};

Stack new_Stack() {
	Stack stack = (Stack)malloc(sizeof(struct Stack));
	stack->list = new_LinkedList();
	return stack;
}

bool Stack_isEmpty(Stack this) {
	return LinkedList_isEmpty(this->list);
}

void Stack_push(Stack this, char* data) {
	LinkedList_add_at_front(this->list, data);
}

char* Stack_pop(Stack this) {
	return (char*)LinkedList_pop(this->list);
}

void Stack_free(Stack this) {
	LinkedList_free(this->list, true);
	free(this);
}
