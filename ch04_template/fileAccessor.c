/*
 * fileReader.c
 *
 *  Created on: 2023. 1. 6.
 *      Author: pcw1029
 */

#include "fileAccessor.h"


bool accessFile(FILE_ACCESSOR_CONTEXT *pstFileAccessorContext)
{
	FILE *pFp = fopen(pstFileAccessorContext->pchFileName, pstFileAccessorContext->pchMode);
	if(pFp == NULL)
		return false;

	pstFileAccessorContext->processer(pstFileAccessorContext, pFp);

	fclose(pFp);
	return true;
}
