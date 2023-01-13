/*
 * fileReader.h
 *
 *  Created on: 2023. 1. 6.
 *      Author: pcw1029
 */

#ifndef FILEACCESSOR_H_
#define FILEACCESSOR_H_

#include <stdio.h>
#include <stdbool.h>
#include "buffer.h"
#include "array_list.h"

#ifdef __cplusplus
extern "C"{
#endif

struct FileAccessorContext;
typedef struct FileErrorObserver{
	void (* const onError)(struct FileErrorObserver *pstThis, struct FileAccessorContext *pstFileAccessorContext);
}FILE_ERROR_OBSERVER;


typedef struct FileAccessorContext{
	FILE* pFp;
	const char * const pchFileName;
	const char * const pchMode;
	ARRAY_LIST stArrayObserverTable;

	bool (* const processer)(struct FileAccessorContext *pstFileAccessorContext);
}FILE_ACCESSOR_CONTEXT;



bool accessFile(FILE_ACCESSOR_CONTEXT *pstFileAccessorContext);
FILE* getFilePointer(FILE_ACCESSOR_CONTEXT* pstFileAccessorContext);
long fileSize(FILE_ACCESSOR_CONTEXT* pstFileAccessorContext);
long fileCurrentPos(FILE_ACCESSOR_CONTEXT *pstFileAccessorContext);
int setFilePos(FILE_ACCESSOR_CONTEXT *pstFileAccessorContext, long offset, int iWhence);
bool readFile(FILE_ACCESSOR_CONTEXT *pstFileAccessorContext, BUFFER_CONTEXT *pstBufferContext);
bool writeFile(FILE_ACCESSOR_CONTEXT *pstFileAccessorContext, BUFFER_CONTEXT *pstBufferContext);
void addFileErrorObserver(FILE_ACCESSOR_CONTEXT* pstFileAccessorContext, FILE_ERROR_OBSERVER *pstFileErrorObserver);
void removeFileErrorObserver(FILE_ACCESSOR_CONTEXT* pstFileAccessorContext, FILE_ERROR_OBSERVER *pstFileErrorObserver);
#ifdef __cplusplus
}
#endif


#endif /* FILEACCESSOR_H_ */
