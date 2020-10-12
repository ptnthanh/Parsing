/*
 * TDP.c
 *
 *  Created on: Oct 7, 2020
 *      Author: thanhpham
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Tree.h"
#include "LinkedList.h"
#include "Stack.h"
#include "TDP.h"

char *nextInputChar;
//Stack stack;
//pNODE root;
int table[8][6] = {
	//		  |   .   *   (   )  a->z
	/*E */	{ 1,  1,  1,  1,  1,   1 },
	/*ET*/	{ 2,  3,  3,  3,  3,   3 },
	/*C */	{ 4,  4,  4,  4,  4,   4 },
	/*CT*/	{ 6,  5,  6,  6,  6,   6 },
	/*S */	{ 7,  7,  7,  7,  7,   7 },
	/*ST*/	{ 9,  9,  8,  9,  9,   9 },
	/*A */	{ 0,  0,  0, 10,  0,  11 },
	/*X */	{ 0,  0,  0,  0,  0,  12 }
};

char letters[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
					'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};


char TDP_Look_Ahead() {
	return *nextInputChar;
}

bool match(char c) {
	if (*nextInputChar == c) {
		nextInputChar++;
		return true;
	} else {
		return false;
	}
}

bool isTerminal(char c) {
	if (c >= 'a' && c <= 'z') return true;
	else if (c=='|' || c=='.' || c=='*' || c=='(' || c==')' || c=='P')
		return true;
	return false;
}

int syncat_to_int(char c) {
	switch(c) {
	case 'E':
		return 0;
	case 'F':
		return 1;
	case 'C':
		return 2;
	case 'D':
		return 3;
	case 'S':
		return 4;
	case 'T':
		return 5;
	case 'A':
		return 6;
	case 'X':
		return 7;
	default:
		return -1;
	}
}

int char_to_int(char c) {
	if (c == '|') return 0;
	else if (c == '.') return 1;
	else if (c == '*') return 2;
	else if (c == '(') return 3;
	else if (c == ')') return 4;
	else if (c >= 'a' && c <= 'z') return 5;
//	else if (c=='E' || c=='F' || c=='C' || c=='D' || c=='S' ||
//			c=='T' || c=='A' || c=='X' || c=='P')
//		return 0;

	return -1;
}

pNODE find_syncat(pNODE root) {
	if (Tree_get_LMC(root) != NULL) {
		pNODE n1 = find_syncat(Tree_get_LMC(root));
		if (n1 != NULL) return n1;
	} else if (!(isTerminal(Tree_get_data(root)))) {
		return root;
	}

	if (Tree_get_RS(root) != NULL) {
		pNODE n2 = find_syncat(Tree_get_RS(root));
		if (n2 != NULL) return n2;
	}
	return NULL;
}

void TDP_select_production(Stack stack, pNODE root, char* c, char lookahead) {
	int production=table[syncat_to_int(*c)][char_to_int(lookahead)];

//	printf("%s: %d\n","Row", syncat_to_int(*c));
//	printf("%s: %d\n","Column", char_to_int(lookahead));


	if (char_to_int(lookahead) == -1)
		production=0;

//	printf("Production: %d\n", production);

	TDP_push_production(stack, root, production, lookahead);
}

void TDP_push_production(Stack stack, pNODE root, int production, char lookahead) {
	pNODE node  = find_syncat(root);
	pNODE  t1, t2, t3;

//	printf("%c\n",Tree_get_data(node));
//	printf("%c\n", lookahead);
//	printf("%d\n\n", !isTerminal(Tree_get_data(root)));

	char arr[2];
	arr[0] = lookahead;
	arr[1] = '\0';
	switch (production) {
//	case -1:
//		return NULL;
	case 0:
		Stack_push(stack, "P");
		Tree_set_LMC(node, Tree_new_Node('P'));
		nextInputChar++;
		break;
	case 1:
		Stack_push(stack, "F");
		Stack_push(stack, "C");

		t1 = Tree_new_Node('C');
		t2 = Tree_new_Node('F');
		Tree_set_LMC(node, t1);
		Tree_set_RS(t1, t2);
		break;
	case 2:
		Stack_push(stack, "E");
//		Stack_push(stack, "|");

		t1 = Tree_new_Node('|');
		t2 = Tree_new_Node('E');
		Tree_set_LMC(node, t1);
		Tree_set_RS(t1, t2);

		nextInputChar++;
		break;
	case 3:
//		Stack_push(stack, "P");
		Tree_set_LMC(node, Tree_new_Node('P'));
		break;
	case 4:
		Stack_push(stack, "D");
		Stack_push(stack, "S");

		t1 = Tree_new_Node('S');
		t2 = Tree_new_Node('D');
		Tree_set_LMC(node, t1);
		Tree_set_RS(t1, t2);
		break;
	case 5:
		Stack_push(stack, "C");
//		Stack_push(stack, ".");

		t1 = Tree_new_Node('.');
		t2 = Tree_new_Node('C');
		Tree_set_LMC(node, t1);
		Tree_set_RS(t1, t2);

		nextInputChar++;
		break;
	case 6:
//		Stack_push(stack, "P");
		Tree_set_LMC(node, Tree_new_Node('P'));
		break;
	case 7:
		Stack_push(stack, "T");
		Stack_push(stack, "A");

		t1 = Tree_new_Node('A');
		t2 = Tree_new_Node('T');
		Tree_set_LMC(node, t1);
		Tree_set_RS(t1, t2);
		break;
	case 8:
		Stack_push(stack, "T");
//		Stack_push(stack, "*");

		t1 = Tree_new_Node('*');
		t2 = Tree_new_Node('T');
		Tree_set_LMC(node, t1);
		Tree_set_RS(t1, t2);

		nextInputChar++;
		break;
	case 9:
//		Stack_push(stack, "P");
		Tree_set_LMC(node, Tree_new_Node('P'));
		break;
	case 10:
		Stack_push(stack, ")");
		Stack_push(stack, "E");
		Stack_push(stack, "(");

		t1 = Tree_new_Node('(');
		t2 = Tree_new_Node('E');
		t3 = Tree_new_Node(')');
		Tree_set_LMC(node, t1);
		Tree_set_RS(t1, t2);
		Tree_set_RS(t2, t3);
		break;
	case 11:
		Stack_push(stack, "X");
		Tree_set_LMC(node, Tree_new_Node('X'));
		break;
	case 12:
		//Stack_push(stack, arr);
		nextInputChar++;
		Tree_set_LMC(node, Tree_new_Node(lookahead));
		break;
	default:
		break;
	}
}

pNODE TDP_parse(char *input) {
	nextInputChar = input;
	Stack stack = new_Stack();
	Stack_push(stack, "E");
	pNODE root = Tree_new_Node('E');

	while (!Stack_isEmpty(stack)) {
		char *y = Stack_pop(stack);
		//printf("%s\n", *y);
		if (isTerminal(*y)) {
			match(*y);

		} else {
			TDP_select_production(stack, root, y, TDP_Look_Ahead());
//			printf("%c\n\n", TDP_Look_Ahead());
		}
	}
//	if (TDP_Look_Ahead() != '\0') return NULL;

	Stack_free(stack);

	return root;
}

