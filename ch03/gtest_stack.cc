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
	int iBuff[16];
	STACK stStack = newStack(iBuff);

	EXPECT_EQ(false, pop(&stStack, &iRet));
}


TEST(StackTest, popStackReturnTrue)
{
	int iRet;
	int iBuff[16];
	STACK stStack = newStack(iBuff);

	EXPECT_EQ(true, push(&stStack, 100));
	EXPECT_EQ(true, pop(&stStack, &iRet));
	EXPECT_EQ(100, iRet);
}

TEST(StackTest, pushToFullStackReturnsFalse)
{
	int iRet;
	int iBuff[16];
	STACK stStack = newStack(iBuff);

	for (int i = 0; i < 16; ++i)
		push(&stStack, i);
	EXPECT_EQ(false, push(&stStack, 100));

	EXPECT_EQ(true, pop(&stStack, &iRet));
	EXPECT_EQ(15, iRet);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
