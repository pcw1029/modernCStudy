/*
 * cdPlayer.c
 *
 *  Created on: 2023. 1. 5.
 *      Author: pcw1029
 */




#include <stdbool.h>
#include "cdPlayer.h"

#ifdef GTEST
	int iCmdIndex = 0;
	const char *apchBuff[10];
#endif

static const STATE *pstCurrentState;

static const STATE *ignore(const STATE *pstState);
static const STATE *startPlay(const STATE *pstState);
static const STATE *stopPlay(const STATE *pstState);
static const STATE *pausePlay(const STATE *pstState);
static const STATE *resumePlay(const STATE *pstState);

const STATE IDLE = {
		ignore,
		startPlay
};

const STATE PLAY = {
		stopPlay,
		pausePlay
};

const STATE PAUSE = {
		stopPlay,
		resumePlay
};

void initialize()
{
#ifdef GTEST
	iCmdIndex = 0;
#endif
	pstCurrentState = &IDLE;
}

void onStop()
{
	pstCurrentState = pstCurrentState->stop(pstCurrentState);
}

void onPlayOrPause()
{
	pstCurrentState = pstCurrentState->playOrPause(pstCurrentState);
}

static const STATE *ignore(const STATE *pstState)
{
	return pstCurrentState;
}

static const STATE *startPlay(const STATE *pstState)
{
#ifdef GTEST
	apchBuff[iCmdIndex++] = "start";
#endif
	return &PLAY;
}

static const STATE *stopPlay(const STATE *pstState)
{
#ifdef GTEST
	apchBuff[iCmdIndex++] = "stop";
#endif
	return &IDLE;
}

static const STATE *pausePlay(const STATE *pstState)
{
#ifdef GTEST
	apchBuff[iCmdIndex++] = "pause";
#endif
	return &PAUSE;
}
static const STATE *resumePlay(const STATE *pstState)
{
#ifdef GTEST
	apchBuff[iCmdIndex++] = "resume";
#endif
	return &PLAY;
}
