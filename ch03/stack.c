/*
 * stack.c
 *
 *  Created on: 2023. 1. 1.
 *      Author: pcw1029
 */



#include <stdbool.h>
#include "stack.h"

static int iBuff[16];
static int iTop = 0;

static bool isStackFull(const STACK *pstStack)
{
	return pstStack->iTop == pstStack->size;
}

static bool isStackEmpty(const STACK *pstStack)
{
	return pstStack->iTop == 0;
}

static bool isRangeOk(const RANGE *pstRange, int iVal)
{
	return pstRange == NULL || (pstRange->iMin <= iVal && pstRange->iMax >= iVal);
}

bool push(STACK *pstStack, int iVal)
{
	if(!isRangeOk(pstStack->pstRange, iVal) || isStackFull(pstStack))
		return false;

	pstStack->pBuff[pstStack->iTop++] = iVal;

	return true;
}

bool pop(STACK *pstStack, int *piRetVal)
{
	if(isStackEmpty(pstStack))
		return false;

	*piRetVal = pstStack->pBuff[--pstStack->iTop];
	return true;
}
