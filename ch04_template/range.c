/*
 * range.c
 *
 *  Created on: 2023. 1. 6.
 *      Author: pcw1029
 */

#include<limits.h>
#include<stdlib.h>
#include<stdio.h>


int range(const char *pFileName)
{
	FILE* pFp = fopen(pFileName, "r");
	if(pFp == NULL)
		return -1;

	int min = INT_MAX;
	int max = INT_MIN;
	char achBuff[256];

	while((fgets(achBuff, sizeof(achBuff), pFp))){
		int value = atoi(achBuff);
		min = (min > value)?value:min;
		max = (max < value)?value:max;
	}
	fclose(pFp);

	return max-min;
}

