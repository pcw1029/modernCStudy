/*
 * array_list.h
 *
 *  Created on: 2023. 1. 13.
 *      Author: pcw1029
 */

#ifndef ARRAY_LIST_H_
#define ARRAY_LIST_H_

#include <stdbool.h>

#ifdef __cplusplus
extern "C"{
#endif

typedef struct ArrayList{
	const int iCapacity;
	void **const pvBuff;
	size_t index;

	struct ArrayList *(* const add)(struct ArrayList *pstArrayList, void *pvData);
	void *(* const remove)(struct ArrayList *pstArrayList, void *pvData);
	void *(* const get)(struct ArrayList *pstArrayList, int iIndex);
	size_t (*const size)(struct ArrayList *pstArrayList);
}ARRAY_LIST;

ARRAY_LIST* addToArrayList(ARRAY_LIST* pstArrayList, void *pvData);
void* removeFromArrayList(ARRAY_LIST* pstArrayList, void *pvData);
void* getFromArrayList(ARRAY_LIST *pstArrayList, int iIndex);
size_t arrayListSize(ARRAY_LIST *pstArrayList);

#define NEW_ARRAY_LIST(array){\
	sizeof(array)/sizeof(void *), array, 0, \
	addToArrayList, removeFromArrayList, getFromArrayList, arrayListSize \
}

#ifdef __cplusplus
}
#endif

#endif /* ARRAY_LIST_H_ */
