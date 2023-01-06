/*
 * fileReader.c
 *
 *  Created on: 2023. 1. 6.
 *      Author: pcw1029
 */

#include "fileReader.h"



int readFile(FILE_READER_CONTEXT *pstFileReaderContext)
{
	FILE* pFp = fopen(pstFileReaderContext->pchFileName, "r");
	if(pFp == NULL)
		return -1;

	pstFileReaderContext->processer(pstFileReaderContext, pFp);

	fclose(pFp);
	return 0;
}
