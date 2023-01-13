/*
 * array_list.c
 *
 *  Created on: 2023. 1. 13.
 *      Author: pcw1029
 */




#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "array_list.h"

ARRAY_LIST* addToArrayList(ARRAY_LIST* pstArrayList, void *pvData)
{
	assert(pstArrayList->iCapacity > pstArrayList->index);
	pstArrayList->pvBuff[pstArrayList->index++] = pvData;
	return pstArrayList;
}

void* removeFromArrayList(ARRAY_LIST* pstArrayList, void *pvData)
{
	for(int i=0; i<pstArrayList->index; ++i){
		if(pstArrayList->pvBuff[i] == pvData){
			memmove(pstArrayList->pvBuff+i, pstArrayList->pvBuff+i+1, (pstArrayList->index -i -1)*sizeof(void *));
			--pstArrayList->index;
			return pvData;
		}
	}
	return NULL;
}

void* getFromArrayList(ARRAY_LIST *pstArrayList, int iIndex)
{
	assert(0<=iIndex && pstArrayList->index > iIndex);
	return pstArrayList->pvBuff[iIndex];
}

size_t arrayListSize(ARRAY_LIST *pstArrayList)
{
	return pstArrayList->index;
}
