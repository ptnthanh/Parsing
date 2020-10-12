/*
 * RDP.c
 *
 *  Created on: Oct 6, 2020
 *      Author: thanhpham
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "Tree.h"
#include "RDP.h"

char *nextInputChar;
pNODE root;

pNODE RDP_parse(char *input) {
	nextInputChar=input;
    root = E();

	return root;
}

bool RDP_Look_Ahead(char c)  {
	return *nextInputChar == c;
}

int match_terminal(char c) {
	if (*nextInputChar == c) {
		nextInputChar++;
		return true;
	} else {
		return false;
	}
}

bool isAlpha(char c) {
	if (c >= 'a' && c <= 'z') {
		return true;
	}
	return false;
}

pNODE E() {
	pNODE E_Node = Tree_new_Node('E');

	if (*nextInputChar == '\n') {
		Tree_set_LMC(E_Node, Tree_new_Node('P'));
	} else {
		pNODE p1 = C();
		if (p1==NULL) return NULL;
		pNODE p2 = ET();
		if (p2==NULL) return NULL;
		Tree_set_LMC(E_Node, p1);
		Tree_set_RS(p1, p2);
	}

	return E_Node;
}

pNODE ET() {
	pNODE ET_Node = Tree_new_Node('F');
	if (!RDP_Look_Ahead('|')) {
		Tree_set_LMC(ET_Node,Tree_new_Node('P'));
	} else {
		if (!match_terminal('|')) return NULL;
		pNODE p1 = E();
		if (p1==NULL) return NULL;
		pNODE temp = Tree_new_Node('|');
		Tree_set_LMC(ET_Node, temp);
		Tree_set_RS(temp, p1);
	}
	return ET_Node;
}

pNODE C() {
	pNODE C_Node = Tree_new_Node('C');

	pNODE p1 = S();
	if (p1 == NULL) return NULL;

	pNODE p2 = CT();
	if (p2 == NULL) return NULL;

	Tree_set_LMC(C_Node, p1);
	Tree_set_RS(p1, p2);

	return C_Node;
}

pNODE CT() {
	pNODE CT_Node = Tree_new_Node('D');

	if (!RDP_Look_Ahead('.')) {
		Tree_set_LMC(CT_Node, Tree_new_Node('P'));
	} else {
		if (!match_terminal('.')) return NULL;
		pNODE p1 = C();
		if (p1 == NULL) return NULL;
		pNODE temp = Tree_new_Node('.');
		Tree_set_LMC(CT_Node, temp);
		Tree_set_RS(temp, p1);
	}

	return CT_Node;
}

pNODE S() {
	pNODE S_Node = Tree_new_Node('S');

	pNODE p1 = A();
	if (p1 == NULL) return NULL;

	pNODE p2 = ST();
	if (p2 == NULL) return NULL;

	Tree_set_LMC(S_Node, p1);
	Tree_set_RS(p1, p2);
	return S_Node;

}

pNODE ST() {
	pNODE ST_Node = Tree_new_Node('T');

	if (!RDP_Look_Ahead('*')) {
		Tree_set_LMC(ST_Node, Tree_new_Node('P'));
	} else {
		if (!match_terminal('*')) return NULL;
		pNODE p1 = ST();
		if (p1 == NULL) return NULL;
		pNODE temp = Tree_new_Node('*');
		Tree_set_LMC(ST_Node, temp);
		Tree_set_RS(temp, p1);
	}

	return ST_Node;
}

pNODE A() {
	pNODE A_Node = Tree_new_Node('A');
	if (!RDP_Look_Ahead('(')) {
		pNODE p1 = X();
		if (p1==NULL) return NULL;
		Tree_set_LMC(A_Node, p1);
	} else {
		if (!match_terminal('(')) return NULL;
		pNODE p1 = E();
		if (p1 == NULL) return NULL;
		if (!match_terminal(')')) return NULL;
		pNODE temp = Tree_new_Node('(');
		Tree_set_LMC(A_Node, temp);
		Tree_set_RS(temp, p1);
		Tree_set_RS(p1,Tree_new_Node(')'));
	}
	return A_Node;
}

pNODE X() {
	pNODE X_Node = Tree_new_Node('X');
	if (!isAlpha(*nextInputChar)) {
		return NULL;
	} else {
		pNODE p1 = Tree_new_Node(*nextInputChar);
		Tree_set_LMC(X_Node, p1);
		nextInputChar++;
	}
	return X_Node;
}
