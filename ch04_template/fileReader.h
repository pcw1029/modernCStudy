/*
 * fileReader.h
 *
 *  Created on: 2023. 1. 6.
 *      Author: pcw1029
 */

#ifndef FILEREADER_H_
#define FILEREADER_H_

#include<stdio.h>

#ifdef __cplusplus
extern "C"{
#endif

typedef struct FileReaderContext{
	const char * const pchFileName;
	void (* const processer)(struct FileReaderContext *pstFileReaderContext, FILE* pFp);
}FILE_READER_CONTEXT;

int readFile(FILE_READER_CONTEXT *pstFileReaderContext);

#ifdef __cplusplus
}
#endif


#endif /* FILEREADER_H_ */
