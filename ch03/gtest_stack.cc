/*
 * gtest_stack.cc
 *
 *  Created on: 2023. 1. 1.
 *      Author: pcw1029
 */


#include "gtest/gtest.h"

#include <stdbool.h>
#include "stack.h"

TEST(StackTest, popEmputyReturnFalse)
{
	int iRet;
	EXPECT_EQ(false, pop(&iRet));
}


TEST(StackTest, popStackReturnTrue)
{
	int iRet;
	EXPECT_EQ(true, push(100));
	EXPECT_EQ(true, pop(&iRet));
	EXPECT_EQ(100, iRet);
}

TEST(StackTest, pushToFullStackReturnsFalse)
{
	int ret;
	for (int i = 0; i < 16; ++i)
		push(i);
	EXPECT_EQ(false, push(100));

	EXPECT_EQ(true, pop(&ret));
	EXPECT_EQ(15, ret);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
