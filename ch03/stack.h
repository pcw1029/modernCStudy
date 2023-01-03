/*
 * stack.h
 *
 *  Created on: 2023. 1. 1.
 *      Author: pcw1029
 */

#ifndef STACK_H_
#define STACK_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct{
	int iTop;
	const size_t size;
	int *const pBuff;
}STACK;

bool push(STACK *pstStack, int iVal);
bool pop(STACK *pstStack, int *piRetVal);

//구조체를 쉽게 초기화 하기위한 매크로
#define newStack(buf) {	\
	0, sizeof(buf)/sizeof(int), (buf)	\
}

#ifdef __cplusplus
}
#endif

#endif /* STACK_H_ */
