/*
 * Tree.c
 *
 *  Created on: Oct 5, 2020
 *      Author: thanhpham
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Tree.h"


struct NODE {
    char data;
    int depth;
    pNODE leftmostChild, rightSibling, parent;
};

pNODE Tree_new_Node(char data){
    pNODE node = (pNODE)malloc(sizeof(struct NODE));
    node->data=data;
    node->depth=0;
    node->leftmostChild=NULL;
    node->rightSibling=NULL;
    node->parent=NULL;
    return node;
}

void Tree_set_Parent(pNODE child, pNODE parent_node){
    child -> parent= parent_node;
}

void Tree_set_LMC(pNODE node, pNODE child){
    node ->leftmostChild = child;
    Tree_set_Parent(child,node);
}

void Tree_set_RS(pNODE node,  pNODE rs){
    node -> rightSibling = rs;
    Tree_set_Parent(rs,node->parent);
}

void Tree_count_depth(pNODE root){
    if(root != NULL){
        root -> depth = Tree_seek_top(root);
        Tree_count_depth(root->leftmostChild);
        Tree_count_depth(root->rightSibling);
    }

}

int Tree_seek_top(pNODE node){
    if(node->parent == NULL)
        return 0;
    else
        return Tree_seek_top(node->parent) +1;
}

void Tree_print(pNODE root){
    Tree_count_depth(root);

    if(root != NULL){
        for(int i=0;i<root->depth; i++)
            printf("  ");
        if (root->data == 'P') {
        	printf("%s\n", "eps");
        } else if (root->data == 'F') {
        	printf("%s\n", "ET");
        } else if (root->data == 'D') {
        	printf("%s\n", "CT");
        } else if (root->data == 'T') {
        	printf("%s\n", "ST");
        } else {
        	 printf("%c\n", root->data);
        }

        Tree_print(root->leftmostChild);
        Tree_print(root->rightSibling);
    }
}

char Tree_get_data(pNODE node){
    return node->data;
}

pNODE Tree_get_LMC(pNODE node){
    return node->leftmostChild;
}

pNODE Tree_get_RS(pNODE node){
    return node->rightSibling;
}

pNODE Tree_get_parent(pNODE node){
    return node->parent;
}

void Tree_free(pNODE root){
    if(root != NULL){
        Tree_free(root->leftmostChild);
        Tree_free(root->rightSibling);
        free(root);
    }
}
