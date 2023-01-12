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

static void doWithBuffer(BUFFER_CONTEXT *pstBufferContext);
static void fileError(CONTEXT *pstContext);
static long fileSize(const char *pchFileName);


INT_SORTER_ERROR intSorter(const char* pchFileName)
{
	CONTEXT stContext = {pchFileName, ERR_CAT_OK};
	long size = fileSize(pchFileName);
	if(size == -1){
		fileError(&stContext);
		return stContext.iErrorCategory;
	}

	MY_BUFFER_CONTEXT stMyBufferContext = {{NULL, size, doWithBuffer}, &stContext};
	if(!buffer(&stMyBufferContext.stBufferContext)){
		stContext.iErrorCategory = ERR_CAT_MEMORY;
	}
	return stContext.iErrorCategory;
}

static void reader(FILE_ACCESSOR_CONTEXT* pstFileAccessorContext, FILE *pFp)
{
	MY_FILE_ACCESSOR_CONTEXT *pstMyFileAccesorContext = (MY_FILE_ACCESSOR_CONTEXT *)pstFileAccessorContext;
	MY_BUFFER_CONTEXT *pstMyBufferContext = pstMyFileAccesorContext->pstMyBufferContext;
//	pstMyBufferContext

	if(pstMyBufferContext->stBufferContext.size != \
			fread(pstMyBufferContext->stBufferContext.pvBuff, sizeof(char), pstMyBufferContext->stBufferContext.size, pFp)){
		fileError(pstMyBufferContext->pstContext);
	}
}

static void writer(FILE_ACCESSOR_CONTEXT* pstFileAccessorContext, FILE *pFp)
{
	size_t size;
	MY_FILE_ACCESSOR_CONTEXT *pstMyFileAccesorContext = (MY_FILE_ACCESSOR_CONTEXT *)pstFileAccessorContext;
	MY_BUFFER_CONTEXT *pstMyBufferContext = pstMyFileAccesorContext->pstMyBufferContext;

	size = fwrite(pstMyBufferContext->stBufferContext.pvBuff, sizeof(char), pstMyBufferContext->stBufferContext.size, pFp);
	if(pstMyBufferContext->stBufferContext.size != size){
		fileError(pstMyBufferContext->pstContext);
	}
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

static void doWithBuffer(BUFFER_CONTEXT *pstBufferContext)
{
	MY_BUFFER_CONTEXT *pstMyBufferContext = (MY_BUFFER_CONTEXT *)pstBufferContext;
	MY_FILE_ACCESSOR_CONTEXT stReadFileAccessorContext = {{pstMyBufferContext->pstContext->pchFileName, "rb", reader}, pstMyBufferContext};
	if(!accessFile(&stReadFileAccessorContext.stFileAccessorContext)){
		fileError(pstMyBufferContext->pstContext);
		return;
	}

	qsort(pstBufferContext->pvBuff, pstBufferContext->size/sizeof(int), sizeof(int), comparator);

	MY_FILE_ACCESSOR_CONTEXT stWriteFileAccessorContext = {{pstMyBufferContext->pstContext->pchFileName, "wb", writer}, pstMyBufferContext};
	if(!accessFile(&stWriteFileAccessorContext.stFileAccessorContext)){
		fileError(pstMyBufferContext->pstContext);
		return;
	}
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


static long fileSize(const char *pchFileName)
{
	SIZE_GETTER_CONTEXT stSizeGetterContext = {{pchFileName, "rb", sizeReader}, 0};

	if(!accessFile(&stSizeGetterContext.stFileAccessorContext)){
		return -1;
	}

	return stSizeGetterContext.size;
}

