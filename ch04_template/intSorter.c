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
static void fileError(FILE_ERROR_OBSERVER* pstFileErrorObserver, FILE_ACCESSOR_CONTEXT *pstFileAccessorContext);

static FILE_ERROR_OBSERVER _stFileErrorObserver = {
	fileError
};

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
	long size = fileSize(pstFileAccessorContext);
	if(size == -1){
		return false;
	}

	if(allocateBuffer(&pstMyFileAccesorContext->pstMyBufferContext->stBufferContext, size)==NULL){
		pstMyFileAccesorContext->pstMyBufferContext->pstContext->iErrorCategory = ERR_CAT_MEMORY;
		return false;
	}

	return readFile(pstFileAccessorContext, &pstMyFileAccesorContext->pstMyBufferContext->stBufferContext);
}

static bool writer(FILE_ACCESSOR_CONTEXT* pstFileAccessorContext)
{
	MY_FILE_ACCESSOR_CONTEXT *pstMyFileAccesorContext = (MY_FILE_ACCESSOR_CONTEXT *)pstFileAccessorContext;

	return writeFile(pstFileAccessorContext, &pstMyFileAccesorContext->pstMyBufferContext->stBufferContext);
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
	MY_FILE_ACCESSOR_CONTEXT stReadFileAccessorContext = {{NULL, pstMyBufferContext->pstContext->pchFileName, "rb", reader, &_stFileErrorObserver}, pstMyBufferContext};
	if(!accessFile(&stReadFileAccessorContext.stFileAccessorContext)){
		return false;
	}

	qsort(pstBufferContext->pvBuff, pstBufferContext->size/sizeof(int), sizeof(int), comparator);

	MY_FILE_ACCESSOR_CONTEXT stWriteFileAccessorContext = {{NULL, pstMyBufferContext->pstContext->pchFileName, "wb", writer, &_stFileErrorObserver}, pstMyBufferContext};
	if(!accessFile(&stWriteFileAccessorContext.stFileAccessorContext)){
		return false;
	}
	return true;
}

static void fileError(FILE_ERROR_OBSERVER* pstFileErrorObserver, FILE_ACCESSOR_CONTEXT *pstFileAccessorContext)
{
	g_stFileErrorObserver.onError(pstFileErrorObserver, pstFileAccessorContext);
	MY_FILE_ACCESSOR_CONTEXT *pstMyFileAccessorContext = (MY_FILE_ACCESSOR_CONTEXT *)pstFileAccessorContext;
	pstMyFileAccessorContext->pstMyBufferContext->pstContext->iErrorCategory = ERR_CAT_FILE;
}

static void sizeReader(FILE_ACCESSOR_CONTEXT *pstFileAccessorContext, FILE* pFp)
{
	SIZE_GETTER_CONTEXT *pstSizeGetterContext = (SIZE_GETTER_CONTEXT *)pstFileAccessorContext;
	pstSizeGetterContext->size = -1;

	if(fseek(pFp, 0, SEEK_END) == 0){
		pstSizeGetterContext->size = ftell(pFp);
	}
}

