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

static void fileError(FILE_ACCESSOR_CONTEXT* pstFileAccessorContext);

bool accessFile(FILE_ACCESSOR_CONTEXT *pstFileAccessorContext)
{
	assert(pstFileAccessorContext);
	bool bRet = pstFileAccessorContext->processer(pstFileAccessorContext);
	if(pstFileAccessorContext->pFp != NULL){
		if(fclose(pstFileAccessorContext->pFp)!=0){
			fileError(pstFileAccessorContext);
			bRet = false;
		}
	}
	return bRet;
}

FILE* getFilePointer(FILE_ACCESSOR_CONTEXT* pstFileAccessorContext)
{
	assert(pstFileAccessorContext);
	if(pstFileAccessorContext->pFp == NULL){
		pstFileAccessorContext->pFp = fopen(pstFileAccessorContext->pchFileName, pstFileAccessorContext->pchMode);
		if(pstFileAccessorContext->pFp == NULL){
			fileError(pstFileAccessorContext);
		}
	}
	return pstFileAccessorContext->pFp;
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

	long lRet = ftell(pFp);
	if(lRet < 0)
		fileError(pstFileAccessorContext);

	return lRet;
}

int setFilePos(FILE_ACCESSOR_CONTEXT *pstFileAccessorContext, long offset, int iWhence)
{
	assert(pstFileAccessorContext);
	FILE* pFp = getFilePointer(pstFileAccessorContext);
	if(pFp == NULL)
		return -1;

	int iRet = fseek(pFp, offset, iWhence);
	if(iRet != 0)
		fileError(pstFileAccessorContext);

	return iRet;
}

bool readFile(FILE_ACCESSOR_CONTEXT *pstFileAccessorContext, BUFFER_CONTEXT *pstBufferContext)
{
	FILE *pFp = getFilePointer(pstFileAccessorContext);
	if(pFp == NULL)
		return false;

	if(pstBufferContext->size != fread(pstBufferContext->pvBuff, sizeof(char), pstBufferContext->size, pFp)){
		fileError(pstFileAccessorContext);
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
		fileError(pstFileAccessorContext);
		return false;
	}
	return true;
}

void addFileErrorObserver(FILE_ACCESSOR_CONTEXT* pstFileAccessorContext, FILE_ERROR_OBSERVER *pstFileErrorObserver){
	ARRAY_LIST *pstArrayList = &pstFileAccessorContext->stArrayObserverTable;
	pstArrayList->add(pstArrayList, pstFileErrorObserver);
}

void removeFileErrorObserver(FILE_ACCESSOR_CONTEXT* pstFileAccessorContext, FILE_ERROR_OBSERVER *pstFileErrorObserver){
	ARRAY_LIST *pstArrayList = &pstFileAccessorContext->stArrayObserverTable;
	pstArrayList->remove(pstArrayList, pstFileErrorObserver);
}

static void fileError(FILE_ACCESSOR_CONTEXT* pstFileAccessorContext)
{
	ARRAY_LIST *pstArrayList = &pstFileAccessorContext->stArrayObserverTable;
	for(int i=0; i<pstArrayList->index; ++i){
		FILE_ERROR_OBSERVER *pstFileErrorObserver = pstArrayList->get(pstArrayList, i);
		pstFileErrorObserver->onError(pstFileErrorObserver, pstFileAccessorContext);
	}
}
