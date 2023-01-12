/*
 * intSorter.c
 *
 *  Created on: 2023. 1. 6.
 *      Author: pcw1029
 */


#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>

#include "intSorter.h"
#include "fileAccessor.h"
#include "buffer.h"

typedef struct {
	BUFFER_CONTEXT stBufferContext;
	CONTEXT *pstContext;
}MY_BUFFER_CONTEXT;

typedef struct{
	FILE_ACCESSOR_CONTEXT stFileAccessorContext;
	MY_BUFFER_CONTEXT *pstMyBufferContext;
}MY_FILE_ACCESSOR_CONTEXT;

typedef struct{
	FILE_ACCESSOR_CONTEXT stFileAccessorContext;
	long size;
}SIZE_GETTER_CONTEXT;

static bool doWithBuffer(BUFFER_CONTEXT *pstBufferContext);
static void fileError(CONTEXT *pstContext);
static long fileSize(FILE_ACCESSOR_CONTEXT* pstFileAccessorContext);


INT_SORTER_ERROR intSorter(const char* pchFileName)
{
	CONTEXT stContext = {pchFileName, ERR_CAT_OK};

	MY_BUFFER_CONTEXT stMyBufferContext = {{NULL, 0, doWithBuffer}, &stContext};
	buffer(&stMyBufferContext.stBufferContext);
	return stContext.iErrorCategory;
}

static bool reader(FILE_ACCESSOR_CONTEXT* pstFileAccessorContext)
{
	MY_FILE_ACCESSOR_CONTEXT *pstMyFileAccesorContext = (MY_FILE_ACCESSOR_CONTEXT *)pstFileAccessorContext;
	MY_BUFFER_CONTEXT *pstMyBufferContext = pstMyFileAccesorContext->pstMyBufferContext;
	long size = fileSize(pstFileAccessorContext);
	if(size == -1){
		fileError(pstMyBufferContext->pstContext);
		return false;
	}

	if(!allocateBuffer(&pstMyBufferContext->stBufferContext.pvBuff, size)){
		pstMyBufferContext->pstContext->iErrorCategory = ERR_CAT_MEMORY;
		return false;
	}

	FILE* pFp = getFilePointer(pstFileAccessorContext);
	if(pstMyBufferContext->stBufferContext.size != \
			fread(pstMyBufferContext->stBufferContext.pvBuff, sizeof(char), pstMyBufferContext->stBufferContext.size, pFp)){
		fileError(pstMyBufferContext->pstContext);
		return false;
	}
	return true;
}

static bool writer(FILE_ACCESSOR_CONTEXT* pstFileAccessorContext)
{
	size_t size;
	MY_FILE_ACCESSOR_CONTEXT *pstMyFileAccesorContext = (MY_FILE_ACCESSOR_CONTEXT *)pstFileAccessorContext;
	MY_BUFFER_CONTEXT *pstMyBufferContext = pstMyFileAccesorContext->pstMyBufferContext;

	FILE* pFp = getFilePointer(pstFileAccessorContext);
	size = fwrite(pstMyBufferContext->stBufferContext.pvBuff, sizeof(char), pstMyBufferContext->stBufferContext.size, pFp);
	if(pstMyBufferContext->stBufferContext.size != size){
		fileError(pstMyBufferContext->pstContext);
		return false;
	}
	return true;
}

static int comparator(const void* pvData1, const void* pvData2){
	int iData1 = *(const int *)pvData1;
	int iData2 = *(const int *)pvData2;
	if(iData1 < iData2)
		return -1;
	if(iData1 > iData2)
		return 1;
	return 0;
}

static bool doWithBuffer(BUFFER_CONTEXT *pstBufferContext)
{
	MY_BUFFER_CONTEXT *pstMyBufferContext = (MY_BUFFER_CONTEXT *)pstBufferContext;
	MY_FILE_ACCESSOR_CONTEXT stReadFileAccessorContext = {{NULL, pstMyBufferContext->pstContext->pchFileName, "rb", reader}, pstMyBufferContext};
	if(!accessFile(&stReadFileAccessorContext.stFileAccessorContext)){
		fileError(pstMyBufferContext->pstContext);
		return false;
	}

	qsort(pstBufferContext->pvBuff, pstBufferContext->size/sizeof(int), sizeof(int), comparator);

	MY_FILE_ACCESSOR_CONTEXT stWriteFileAccessorContext = {{NULL, pstMyBufferContext->pstContext->pchFileName, "wb", writer}, pstMyBufferContext};
	if(!accessFile(&stWriteFileAccessorContext.stFileAccessorContext)){
		fileError(pstMyBufferContext->pstContext);
		return false;
	}
	return true;
}

static void fileError(CONTEXT *pstContext)
{
	fprintf(stderr,"%s:%s\n", pstContext->pchFileName, strerror(errno));
	pstContext->iErrorCategory = ERR_CAT_FILE;
}

static void sizeReader(FILE_ACCESSOR_CONTEXT *pstFileAccessorContext, FILE* pFp)
{
	SIZE_GETTER_CONTEXT *pstSizeGetterContext = (SIZE_GETTER_CONTEXT *)pstFileAccessorContext;
	pstSizeGetterContext->size = -1;

	if(fseek(pFp, 0, SEEK_END) == 0){
		pstSizeGetterContext->size = ftell(pFp);
	}
}

static long fileCurrentPos(FILE_ACCESSOR_CONTEXT *pstFileAccessorContext)
{
	assert(pstFileAccessorContext);
	FILE *pFp = getFilePointer(pstFileAccessorContext);
	if(pFp == NULL)
		return -1;
	return ftell(pFp);
}

static int setFilePos(FILE_ACCESSOR_CONTEXT *pstFileAccessorContext, long offset, int iWhence)
{
	assert(pstFileAccessorContext);
	FILE* pFp = getFilePointer(pstFileAccessorContext);
	if(pFp == NULL)
		return -1;
	return fseek(pFp, offset, iWhence);
}

static long fileSize(FILE_ACCESSOR_CONTEXT* pstFileAccessorContext)
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

