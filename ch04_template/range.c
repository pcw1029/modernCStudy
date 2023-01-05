/*
 * range.c
 *
 *  Created on: 2023. 1. 6.
 *      Author: pcw1029
 */

#include<limits.h>
#include<stdlib.h>
#include<stdio.h>



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

int readFile(const char *pFileName, int (*processor)(FILE *pFp))
{
	FILE* pFp = fopen(pFileName, "r");
	if(pFp == NULL)
		return -1;

	int iRetValue = processor(pFp);

	fclose(pFp);
	return iRetValue;
}

int range(const char *pFileName)
{
	return readFile(pFileName, rangeProcessor);
}

