/*
 * fileReader.c
 *
 *  Created on: 2023. 1. 6.
 *      Author: pcw1029
 */

#include "fileAccessor.h"
#include <assert.h>

bool accessFile(FILE_ACCESSOR_CONTEXT *pstFileAccessorContext)
{
	assert(pstFileAccessorContext);
	bool bRet = pstFileAccessorContext->processer(pstFileAccessorContext);
	if(pstFileAccessorContext->pFp != NULL){
		if(fclose(pstFileAccessorContext->pFp)!=0)
			bRet = false;
	}
	return bRet;
}

FILE* getFilePointer(FILE_ACCESSOR_CONTEXT* pstFileAccessorContext)
{
	assert(pstFileAccessorContext);
	if(pstFileAccessorContext->pFp == NULL)
		pstFileAccessorContext->pFp = fopen(pstFileAccessorContext->pchFileName, pstFileAccessorContext->pchMode);
	return pstFileAccessorContext->pFp;
}
