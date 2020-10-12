/*
 * rexp.c
 *
 *  Created on: Oct 5, 2020
 *      Author: thanhpham
 */


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Tree.h"
#include "LinkedList.h"
#include "Stack.h"
#include "RDP.h"
#include "TDP.h"
#include "expressions.h"


int main(int argc, char *argv[]) {
	while (true) {
		printf("\nEnter your input (\"quit\" to quit): ");
		char input[100];

		scanf(" %s", input);
		if (strcmp("quit",input) == 0) {
			break;
		}
		printf("\nRECURSIVE DESCENT PARSING\n");

		pNODE root = RDP_parse(input);

		if (root==NULL) {
			printf("Input is not well formed!\n");
		} else {
			Tree_print(root);
		}



		printf("\nTABLE DRIVEN PARSING\n");

		root = TDP_parse(input);

		if (root==NULL) {
			printf("Input is not well formed!\n");
		} else {
			Tree_print(root);

			printf("\nPREFIX NOTATION\n");

			char * expr = expression_tree( root);
			if (strcmp(expr, "\0") == 0)
				printf("Empty expression string");
			else printf("\n%s\n", expr);
		}

		Tree_free(root);
	}

}
