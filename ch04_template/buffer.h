/*
 * buffer.h
 *
 *  Created on: 2023. 1. 6.
 *      Author: pcw1029
 */

#ifndef BUFFER_H_
#define BUFFER_H_

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct BufferContext {
	void *pvBuff;
	size_t size;
	bool (*processor)(struct BufferContext *pstBufferContext);
}BUFFER_CONTEXT;

void* allocateBuffer(BUFFER_CONTEXT* pstBufferContext, size_t size);
bool buffer(BUFFER_CONTEXT *pstBufferContext);
#ifdef __cplusplus
}
#endif


#endif /* BUFFER_H_ */
