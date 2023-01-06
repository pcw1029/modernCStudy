/*
 * range.c
 *
 *  Created on: 2023. 1. 6.
 *      Author: pcw1029
 */

#include "fileReader.h"
#include<limits.h>
#include<stdlib.h>
#include<stdio.h>

typedef struct {
	FILE_READER_CONTEXT stBase;
	int iResult;
}MY_FILE_READER_CONTEXT;

static int rangeProcessor(FILE* pFp)
{
	int min = INT_MAX;
	int max = INT_MIN;
	char achBuff[256];

	while((fgets(achBuff, sizeof(achBuff), pFp))){
		int value = atoi(achBuff);
		min = (min > value)?value:min;
		max = (max < value)?value:max;
	}
	return max-min;
}


static void calculateRange(FILE_READER_CONTEXT *pstFileReaderContext, FILE *pFp)
{
	MY_FILE_READER_CONTEXT *pstMyFileReaderContext = (MY_FILE_READER_CONTEXT *)pstFileReaderContext;
	pstMyFileReaderContext->iResult = rangeProcessor(pFp);
}

int range(const char *pchFileName)
{
	MY_FILE_READER_CONTEXT stMyFileReaderContext = {{pchFileName, calculateRange}, 0};

	if(readFile(&stMyFileReaderContext.stBase) != 0){
		fprintf(stderr,"Cannot open file %s\n", pchFileName);
	}
	return stMyFileReaderContext.iResult;
}
