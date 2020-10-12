/*
 * expressions.c
 *
 *  Created on: Oct 9, 2020
 *      Author: thanhpham
 */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "Tree.h"
#include "LinkedList.h"
#include "Stack.h"
#include "RDP.h"
#include "TDP.h"
#include "expressions.h"

bool isOperand(char c) {
	if (c >= 'a' && c <= 'z') return true;
	return false;
}

bool isOperator(char c) {
	if (c == '.' || c == '|' || c == '*') return true;
	return false;
}

char *concatenate(char *a, char *b, char *c, char *d) {
  int size = strlen(a) + strlen(b) + strlen(c) + strlen(d) + 1;
  char *str = malloc(size);
  strcpy (str, a);
  strcat (str, b);
  strcat (str, c);
  strcat (str, d);

  return str;
}

char *concat(char *a, char *b, char *c) {
	int size = strlen(a) + strlen(b) + strlen(c) + 1;
	char *str = malloc(size);
	strcpy(str, a);
	strcat(str, b);
	strcat(str, c);
	return str;
}

char* expression_tree(pNODE root) {
	//char *result = "";
	char data = Tree_get_data(root);
	pNODE lmc = Tree_get_LMC(root);
	pNODE rs = Tree_get_RS(root);
//	printf("%c\n", data);
//	printf("%d\n", isOperand(data));
//	printf("%d\n", isOperator(Tree_get_data(Tree_get_LMC(rs))));
	if (root==NULL) return "Empty tree, no prefix notation.";

	if (isOperand(data)) {
		char arr[2];
		arr[0]=data;
		arr[1]='\0';
		return concat("(ATOMIC ", arr, ")");
	}

//	char check = Tree_get_data(Tree_get_LMC(Tree_get_RS(lmc)));
//	if (isOperator(check)) {
//		if (check == '|') {
//			result = "(UNION ";
//		} else if (check == '*') {
//			result = "(CLOSURE ";
//		} else if (check == '.') {
//			result = "(CONCAT ";
//		}
//		result = strcat(result, expression_tree(lmc));
//		return strcat(result, expression_tree(Tree_get_RS(Tree_get_LMC(Tree_get_RS(lmc)))));
//	}

	else if (data == 'E')
		return expression_tree(lmc);
	else if (data == 'F') {
		return expression_tree(lmc);
	}

	else if (data == 'C') {
		if (rs == NULL)
			return expression_tree(lmc);
		if (!isOperator(Tree_get_data(Tree_get_LMC(rs))))
			return expression_tree(lmc);
		else {
			return concatenate("(UNION ", expression_tree(lmc), expression_tree(Tree_get_RS(Tree_get_LMC(rs))), ")");
		}
	}

	else if (data == 'D') {
		return expression_tree(lmc);
	}

	else if (data == 'S') {
		if (!isOperator(Tree_get_data(Tree_get_LMC(rs))))
			return expression_tree(lmc);
		else
			return concatenate("(CONCAT ", expression_tree(lmc), expression_tree(Tree_get_RS(Tree_get_LMC(rs))), ")");
	}

	else if (data == 'T') {
		return expression_tree(lmc);
	}

	else if (data == 'A') {
//		if (Tree_get_data(Tree_get_LMC(rs)) == 'P') {
//			return expression_tree(lmc);
//		}
//		else
//			return concatenate(expression_tree(Tree_get_RS(lmc)), "(CLOSURE ", expression_tree(Tree_get_RS(Tree_get_LMC(rs))), ")");

		if (Tree_get_data(lmc) == '(') {
			if (Tree_get_data(Tree_get_LMC(rs)) == 'P')
				return expression_tree(Tree_get_RS(lmc));
			else
				return concatenate(expression_tree(Tree_get_RS(lmc)), "(CLOSURE ", expression_tree(Tree_get_RS(Tree_get_LMC(rs))), ")");
		} else { //lmc->data == 'X'
			if (Tree_get_data(Tree_get_LMC(rs)) == 'P')
				return expression_tree(lmc);
			else
				return concatenate("(CLOSURE ", expression_tree(lmc), expression_tree(Tree_get_RS(Tree_get_LMC(rs))), ")");
		}
	}

	else if (data == 'T') {
		if (Tree_get_data(lmc) == 'P')
			return "";

	}

	else if (data == 'X') {
		if (isOperand(Tree_get_data(lmc))) {
			return expression_tree(lmc);
		}
		else
			return "Problem with X";
	}
	else if (data == 'P') {
		return "";
	}

	return "";
}

