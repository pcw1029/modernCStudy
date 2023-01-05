/*
 * gtest_range.cc
 *
 *  Created on: 2023. 1. 6.
 *      Author: pcw1029
 */

#include "range.h"
#include "gtest/gtest.h"


TEST(TemplateTest, normalCase)
{
	char achTmpFileName[L_tmpnam+1];
	tmpnam(achTmpFileName);

	FILE *pFp = fopen(achTmpFileName, "w");

	fputs("1231\n", pFp);
	fputs("1\n", pFp);
	fputs("441\n", pFp);

	EXPECT_EQ(0, fclose(pFp));
	EXPECT_EQ(1230, range(achTmpFileName));
}

TEST(TemplateTest, emptyFile)
{
	char achTmpFileName[L_tmpnam+1];
	tmpnam(achTmpFileName);

	FILE *pFp = fopen(achTmpFileName, "w");
	EXPECT_EQ(0, fclose(pFp));

	EXPECT_EQ(1, range(achTmpFileName));
}


int main(int argc, char** argv){
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
