/*
 * cdPlayer.c
 *
 *  Created on: 2023. 1. 5.
 *      Author: pcw1029
 */




#include <stdbool.h>
#include "cdPlayer.h"

static STATE eCurrentState;

#ifdef GTEST
	int iCmdIndex = 0;
	const char *apchBuff[10];
#endif

void initialize()
{
#ifdef GTEST
	iCmdIndex = 0;
#endif
	eCurrentState = STATE_IDLE;
}

void onEvent(EVENT_CODE eEc)
{
	switch(eCurrentState){
	case STATE_IDLE:
		if(eEc == EV_PLAY_PAUSE)
			startPlayer();
		break;
	case STATE_PLAY:
		if(eEc == EV_PLAY_PAUSE)
			pausePlayer();
		else if(eEc == EV_STOP)
			stopPlayer();
		break;
	case STATE_PAUSE:
		if(eEc == EV_PLAY_PAUSE)
			resumePlayer();
		else if(eEc == EV_STOP)
			stopPlayer();
		break;
	default:
		break;
	}
}

void stopPlayer()
{
	eCurrentState = STATE_IDLE;
#ifdef GTEST
	apchBuff[iCmdIndex++] = "stop";
#endif
}

void pausePlayer()
{
	eCurrentState = STATE_PAUSE;
#ifdef GTEST
	apchBuff[iCmdIndex++] = "pause";
#endif
}

void resumePlayer()
{
	eCurrentState = STATE_PLAY;
#ifdef GTEST
	apchBuff[iCmdIndex++] = "resume";
#endif
}

void startPlayer()
{
	eCurrentState = STATE_PLAY;
#ifdef GTEST
	apchBuff[iCmdIndex++] = "start";
#endif
}
