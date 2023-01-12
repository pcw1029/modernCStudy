/*
 * buffer.c
 *
 *  Created on: 2023. 1. 6.
 *      Author: pcw1029
 */


#include <stdlib.h>
#include <assert.h>
#include "buffer.h"

bool buffer(BUFFER_CONTEXT *pstBufferContext)
{
	assert(pstBufferContext);
	bool bRet = pstBufferContext->processor(pstBufferContext);
	free(pstBufferContext->pvBuff);
	return bRet;
}

void* allocateBuffer(BUFFER_CONTEXT* pstBufferContext, size_t size)
{
	assert(pstBufferContext);
	assert(pstBufferContext->pvBuff == NULL);
	pstBufferContext->pvBuff = malloc(size);
	pstBufferContext->size = size;
	return pstBufferContext->pvBuff;
}
