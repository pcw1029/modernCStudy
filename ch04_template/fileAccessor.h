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

#ifdef __cplusplus
extern "C"{
#endif


typedef struct FileAccessorContext{
	FILE* pFp;
	const char * const pchFileName;
	const char * const pchMode;
	bool (* const processer)(struct FileAccessorContext *pstFileAccessorContext);
}FILE_ACCESSOR_CONTEXT;


bool accessFile(FILE_ACCESSOR_CONTEXT *pstFileAccessorContext);
FILE* getFilePointer(FILE_ACCESSOR_CONTEXT* pstFileAccessorContext);

#ifdef __cplusplus
}
#endif


#endif /* FILEACCESSOR_H_ */
