/*
 * TDP.h
 *
 *  Created on: Oct 7, 2020
 *      Author: thanhpham
 */

#ifndef TDP_H_
#define TDP_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Tree.h"
#include "LinkedList.h"
#include "Stack.h"

//typedef struct _TD_PARSER* TD_PARSER;
//
//struct _TD_PARSER{
//  int curr;
//  int length;
//  pNODE tree;
//};


extern char *nextInputChar;
extern Stack stack;
//extern pNODE root;
//extern int table[8][6];

extern char TDP_Look_Ahead();
extern bool match(char c);

//extern TD_PARSER new_TD_PARSER(char* in, int len);
extern bool isTerminal(char c);
extern int syncat_to_int(char c);
extern int char_to_int(char c);
extern pNODE find_Syntactic_Category(pNODE root);
extern void TDP_select_production(Stack stack, pNODE root, char *c, char lookahead);
extern void TDP_push_production(Stack stack, pNODE root, int production, char lookahead);
extern pNODE TDP_parse(char* input);

#endif /* TDP_H_ */
