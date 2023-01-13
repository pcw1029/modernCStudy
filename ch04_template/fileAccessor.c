/*
 * fileReader.c
 *
 *  Created on: 2023. 1. 6.
 *      Author: pcw1029
 */

#include "fileAccessor.h"
#include <assert.h>
#include <errno.h>
#include <string.h>

static void defaultFileErrorHandler(FILE_ERROR_OBSERVER *pstThis, FILE_ACCESSOR_CONTEXT *pstFileAccessorContext);
FILE_ERROR_OBSERVER g_stFileErrorObserver = {
		&defaultFileErrorHandler
};

bool accessFile(FILE_ACCESSOR_CONTEXT *pstFileAccessorContext)
{
	assert(pstFileAccessorContext);
	if(pstFileAccessorContext->pstFileErrorObserver == NULL)
		pstFileAccessorContext->pstFileErrorObserver = &g_stFileErrorObserver;
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
	if(pstFileAccessorContext->pFp == NULL){
		pstFileAccessorContext->pFp = fopen(pstFileAccessorContext->pchFileName, pstFileAccessorContext->pchMode);
		if(pstFileAccessorContext->pFp == NULL)
			pstFileAccessorContext->pstFileErrorObserver->onError(pstFileAccessorContext->pstFileErrorObserver, pstFileAccessorContext);
	}
	return pstFileAccessorContext->pFp;
}

static void defaultFileErrorHandler(FILE_ERROR_OBSERVER *pstThis, FILE_ACCESSOR_CONTEXT *pstFileAccessorContext)
{
	fprintf(stderr,"File access error %s(mode:%s):%s\n", pstFileAccessorContext->pchFileName, \
			pstFileAccessorContext->pchMode, strerror(errno));
}

long fileSize(FILE_ACCESSOR_CONTEXT* pstFileAccessorContext)
{
	long size = fileCurrentPos(pstFileAccessorContext);
	if(size < 0)
		return -1;

	if(setFilePos(pstFileAccessorContext, 0, SEEK_END)!=0)
		return -1;

	size = fileCurrentPos(pstFileAccessorContext);
	if(setFilePos(pstFileAccessorContext, 0, SEEK_SET)!=0)
		return -1;

	return size;
}

long fileCurrentPos(FILE_ACCESSOR_CONTEXT *pstFileAccessorContext)
{
	assert(pstFileAccessorContext);
	FILE *pFp = getFilePointer(pstFileAccessorContext);
	if(pFp == NULL)
		return -1;
	return ftell(pFp);
}

int setFilePos(FILE_ACCESSOR_CONTEXT *pstFileAccessorContext, long offset, int iWhence)
{
	assert(pstFileAccessorContext);
	FILE* pFp = getFilePointer(pstFileAccessorContext);
	if(pFp == NULL)
		return -1;
	return fseek(pFp, offset, iWhence);
}

bool readFile(FILE_ACCESSOR_CONTEXT *pstFileAccessorContext, BUFFER_CONTEXT *pstBufferContext)
{
	FILE *pFp = getFilePointer(pstFileAccessorContext);
	if(pFp == NULL)
		return false;

	if(pstBufferContext->size != fread(pstBufferContext->pvBuff, sizeof(char), pstBufferContext->size, pFp)){
		pstFileAccessorContext->pstFileErrorObserver->onError(pstFileAccessorContext->pstFileErrorObserver, pstFileAccessorContext);
		return false;
	}
	return true;
}

bool writeFile(FILE_ACCESSOR_CONTEXT *pstFileAccessorContext, BUFFER_CONTEXT *pstBufferContext)
{
	FILE *pFp =  getFilePointer(pstFileAccessorContext);
	if(pFp == NULL)
		return false;

	if(pstBufferContext->size != fwrite(pstBufferContext->pvBuff, sizeof(char), pstBufferContext->size, pFp)){
		pstFileAccessorContext->pstFileErrorObserver->onError(pstFileAccessorContext->pstFileErrorObserver, pstFileAccessorContext);
		return false;
	}
	return true;
}
