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
	const int iMin;
	const int iMax;
}RANGE;

typedef struct{
	int iTop;
	const size_t size;
	int *const pBuff;	//C99에서는 구조체 멤버의 배열이 마지막에 있는 경우에만 해당 배열 요소를 생략할 수 있다. 그리고 그 구조체를 생성할 때 크기를 지정할 수 있다.

	const RANGE * const pstRange;
}STACK;

bool push(STACK *pstStack, int iVal);
bool pop(STACK *pstStack, int *piRetVal);

//구조체를 쉽게 초기화 하기위한 매크로
#define newStack(buf) {	\
	0, (sizeof(buf)/sizeof(int)), (buf)	\
}

#define newStackWithRangeCheck(buf, pstRange) {	\
	0, sizeof(buf)/sizeof(int), (buf),	\
	pstRange	\
}

#ifdef __cplusplus
}
#endif

#endif /* STACK_H_ */
