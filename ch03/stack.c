/*
 * stack.c
 *
 *  Created on: 2023. 1. 1.
 *      Author: pcw1029
 */



#include <stdbool.h>
#include "stack.h"

int iBuff[16];
int iTop = 0;

bool isStackFull(void)
{
	return iTop == sizeof(iBuff)/sizeof(int);
}

bool isStackEmpty(void)
{
	return iTop == 0;
}


bool push(int iVal)
{
	if(isStackFull())
		return false;

	iBuff[iTop++] = iVal;
	return true;
}

bool pop(int *piRetVal)
{
	if(isStackEmpty())
		return false;

	*piRetVal = iBuff[--iTop];
	return true;
}
