/*
 * gtest_range.cc
 *
 *  Created on: 2023. 1. 6.
 *      Author: pcw1029
 */

#include "intSorter.h"
#include "gtest/gtest.h"
#include <stdio.h>
#include <stdbool.h>

static bool writeInt(FILE* pFp, int iData)
{
	return fwrite(&iData, sizeof(int), 1, pFp) == 1;
}

static int readInt(FILE* pFp)
{
	int iRetValue;
	fread(&iRetValue, sizeof(int), 1, pFp);
	return iRetValue;
}

TEST(TemplateTest, normalCase)
{
	char achTmpFileName[L_tmpnam+1];
	tmpnam(achTmpFileName);

	FILE *pFp = fopen(achTmpFileName, "wb");

	EXPECT_EQ(true, writeInt(pFp, 1231));
	EXPECT_EQ(true, writeInt(pFp, 1));
	EXPECT_EQ(true, writeInt(pFp, 441));
	EXPECT_EQ(0, fclose(pFp));

	intSorter(achTmpFileName);

	pFp = fopen(achTmpFileName, "rb");
	EXPECT_EQ(1, readInt(pFp));
	EXPECT_EQ(441, readInt(pFp));
	EXPECT_EQ(1231, readInt(pFp));
	EXPECT_EQ(0, fclose(pFp));
}

TEST(TemplateTest, emptyFile)
{
	char achTmpFileName[L_tmpnam+1];
	tmpnam(achTmpFileName);

	FILE *pFp = fopen(achTmpFileName, "w");
	EXPECT_EQ(0, fclose(pFp));

	intSorter("aaa");
}



int main(int argc, char** argv){
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
