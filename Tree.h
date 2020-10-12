/*
 * Tree.h
 *
 *  Created on: Oct 5, 2020
 *      Author: thanhpham
 */

#ifndef TREE_H_
#define TREE_H_

#include <stdio.h>
#include <stdlib.h>
#include "stdbool.h"

typedef struct NODE *pNODE;
struct Node;

extern pNODE Tree_new_Node(char data);

extern void Tree_set_Parent(pNODE child, pNODE parent_node);

extern void Tree_set_LMC(pNODE node, pNODE child);

extern void Tree_set_RS(pNODE node,  pNODE rs);

extern void Tree_count_depth(pNODE root);

extern int Tree_seek_top(pNODE node);

extern void Tree_print(pNODE root);

extern char Tree_get_data(pNODE node);

extern pNODE Tree_get_LMC(pNODE node);

extern pNODE Tree_get_RS(pNODE node);

extern pNODE Tree_get_parent(pNODE node);

extern void Tree_free(pNODE root);

#endif /* TREE_H_ */
