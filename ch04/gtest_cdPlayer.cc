/*
 * gtest_cdPlayer.cc
 *
 *  Created on: 2023. 1. 5.
 *      Author: pcw1029
 */

#include "gtest/gtest.h"
#include "cdPlayer.h"


TEST(PlayTest, playOnIdleWillStartPlaying)
{
	initialize();
	onEvent(EV_PLAY_PAUSE);
	EXPECT_EQ(1, iCmdIndex);
	ASSERT_TRUE(strcmp(apchBuff[iCmdIndex-1], "start")==0);

	onEvent(EV_PLAY_PAUSE);
	EXPECT_EQ(2, iCmdIndex);
	ASSERT_TRUE(strcmp(apchBuff[iCmdIndex-1], "pause")==0);

	onEvent(EV_PLAY_PAUSE);
	EXPECT_EQ(3, iCmdIndex);
	ASSERT_TRUE(strcmp(apchBuff[iCmdIndex-1], "resume")==0);
}

TEST(StopTest, playOnIdleAndStopWillStopPlaying)
{
	initialize();
	onEvent(EV_PLAY_PAUSE);
	EXPECT_EQ(1, iCmdIndex);
	ASSERT_TRUE(strcmp(apchBuff[iCmdIndex-1], "start")==0);

	onEvent(EV_STOP);
	EXPECT_EQ(2, iCmdIndex);
	ASSERT_TRUE(strcmp(apchBuff[iCmdIndex-1], "stop")==0);
}

TEST(PlayTest, playOnIdleAndPauseAndWillStopPlaying)
{
	initialize();
	onEvent(EV_PLAY_PAUSE);
	EXPECT_EQ(1, iCmdIndex);
	ASSERT_TRUE(strcmp(apchBuff[iCmdIndex-1], "start")==0);

	onEvent(EV_PLAY_PAUSE);
	EXPECT_EQ(2, iCmdIndex);
	ASSERT_TRUE(strcmp(apchBuff[iCmdIndex-1], "pause")==0);

	onEvent(EV_STOP);
	EXPECT_EQ(3, iCmdIndex);
	ASSERT_TRUE(strcmp(apchBuff[iCmdIndex-1], "stop")==0);
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
