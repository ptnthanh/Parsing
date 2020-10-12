/*
 * RDP.h
 *
 *  Created on: Oct 5, 2020
 *      Author: thanhpham
 */

#ifndef RDP_H_
#define RDP_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Tree.h"

extern char *nextInputChar;
extern pNODE root;

extern pNODE RDP_parse(char *input);
extern bool RDP_Look_Ahead(char c);
extern int match_terminal(char c);
extern bool isAlpha(char c);
extern pNODE E();
extern pNODE ET();
extern pNODE C();
extern pNODE CT();
extern pNODE S();
extern pNODE ST();
extern pNODE A();
extern pNODE X();

#endif /* RDP_H_ */
