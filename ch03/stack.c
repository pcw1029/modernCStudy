/*
 * stack.c
 *
 *  Created on: 2023. 1. 1.
 *      Author: pcw1029
 */



#include <stdbool.h>
#include "stack.h"


static bool isStackFull(const STACK *pstStack)
{
	return pstStack->iTop == pstStack->size;
}

static bool isStackEmpty(const STACK *pstStack)
{
	return pstStack->iTop == 0;
}


bool validateRange(VALIDATOR* pstValidator, int iVal)
{
	RANGE* pstRange;
	pstRange = (RANGE *)(pstValidator->pData);
	return (pstRange->iMin <= iVal && pstRange->iMax >= iVal);
}

bool validatePrevious(VALIDATOR* pstValidator, int iVal)
{
	PREVIOUS_DATA *pstPrevData;
	pstPrevData = (PREVIOUS_DATA *)(pstValidator->pData);
	if(pstPrevData->iPrevData == iVal)
		return false;
	pstPrevData->iPrevData = iVal;
	return true;
}

bool validate(VALIDATOR* pstValidator, int iVal)
{
	if(!pstValidator)
		return true;
	return pstValidator->validate(pstValidator, iVal);
}

bool push(STACK *pstStack, int iVal)
{
	if(!validate(pstStack->pstValidator, iVal) || isStackFull(pstStack))
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
