/*
 * gtest_array_list.cc
 *
 *  Created on: 2023. 1. 13.
 *      Author: pcw1029
 */


#include"gtest/gtest.h"
#include<stdio.h>
#include "array_list.h"

TEST(ArrayListTest, addTest){
	void *pvData[2];
	ARRAY_LIST stArrayList = NEW_ARRAY_LIST(pvData);

	ASSERT_EQ(2, stArrayList.iCapacity);
	ASSERT_EQ((size_t)0, stArrayList.size(&stArrayList));
	ASSERT_EQ(pvData, stArrayList.pvBuff);

	char chString1[] = "Hello";
	stArrayList.add(&stArrayList, chString1);
	ASSERT_EQ(2, stArrayList.iCapacity);
	ASSERT_EQ((size_t)1, stArrayList.size(&stArrayList));
	ASSERT_EQ(pvData, stArrayList.pvBuff);

	char chString2[] = "World";
	stArrayList.add(&stArrayList, chString2);
	ASSERT_EQ(2, stArrayList.iCapacity);
	ASSERT_EQ((size_t)2, stArrayList.size(&stArrayList));
	ASSERT_EQ(pvData, stArrayList.pvBuff);

	char chString3[] = "Overflow";
	//Assertion `pstArrayList->iCapacity > pstArrayList->index' failed.
	ASSERT_DEATH(stArrayList.add(&stArrayList, chString3), ".*Assertion .* failed");

}
