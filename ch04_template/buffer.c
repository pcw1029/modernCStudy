/*
 * buffer.c
 *
 *  Created on: 2023. 1. 6.
 *      Author: pcw1029
 */


#include <stdlib.h>
#include "buffer.h"

bool buffer(BUFFER_CONTEXT *pstBufferContext)
{
	pstBufferContext->pvBuff = malloc(pstBufferContext->size);
	if(pstBufferContext->pvBuff == NULL)
		return false;

	pstBufferContext->processor(pstBufferContext);

	free(pstBufferContext->pvBuff);
	return true;
}
