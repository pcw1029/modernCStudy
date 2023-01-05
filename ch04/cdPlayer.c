/*
 * cdPlayer.c
 *
 *  Created on: 2023. 1. 5.
 *      Author: pcw1029
 */




#include <stdbool.h>
#include "cdPlayer.h"

bool bPlayFlag;
bool bPauseFlag;

#ifdef GTEST
	int iCmdIndex = 0;
	const char *apchBuff[10];
#endif

void initialize()
{
#ifdef GTEST
	iCmdIndex = 0;

#endif
	bPlayFlag = false;
	bPauseFlag = false;
}

void onEvent(EVENT_CODE eEc)
{
	switch(eEc){
	case EV_STOP:
		if(bPlayFlag == true || bPauseFlag == true)
			stopPlayer();
		break;
	case EV_PLAY_PAUSE:
		if(bPlayFlag == true)
			pausePlayer();
		else if(bPauseFlag == true)
			resumePlayer();
		else
			startPlayer();
		break;
	default:
		break;
	}
}

void stopPlayer()
{
	bPauseFlag = false;
	bPlayFlag = false;
#ifdef GTEST
	apchBuff[iCmdIndex++] = "stop";
#endif
}

void pausePlayer()
{
	bPauseFlag = true;
	bPlayFlag = false;
#ifdef GTEST
	apchBuff[iCmdIndex++] = "pause";
#endif
}

void resumePlayer()
{
	bPauseFlag = false;
	bPlayFlag = true;
#ifdef GTEST
	apchBuff[iCmdIndex++] = "resume";
#endif
}

void startPlayer()
{
	bPauseFlag = false;
	bPlayFlag = true;
#ifdef GTEST
	apchBuff[iCmdIndex++] = "start";
#endif
}
