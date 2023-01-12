/*
 * intSorter.h
 *
 *  Created on: 2023. 1. 6.
 *      Author: pcw1029
 */

#ifndef INTSORTER_H_
#define INTSORTER_H_

#include "fileAccessor.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum{
	ERR_CAT_OK = 0,
	ERR_CAT_FILE,
	ERR_CAT_MEMORY
}INT_SORTER_ERROR;

typedef struct {
	const char * const pchFileName;
	int iErrorCategory;
}CONTEXT;

INT_SORTER_ERROR intSorter(const char *pchFileName);

#ifdef __cplusplus
}
#endif


#endif /* INTSORTER_H_ */
