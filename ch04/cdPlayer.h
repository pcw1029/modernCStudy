/*
 * cdPlayer.h
 *
 *  Created on: 2023. 1. 5.
 *      Author: pcw1029
 */

#ifndef CDPLAYER_H_
#define CDPLAYER_H_

#ifdef __cplusplus
extern "C" {
#endif


typedef enum {
	EV_STOP,
	EV_PLAY_PAUSE
}EVENT_CODE;

typedef enum {
	STATE_IDLE,
	STATE_PLAY,
	STATE_PAUSE
}STATE;

void initialize();
void onEvent(EVENT_CODE eEc);
void stopPlayer();
void pausePlayer();
void resumePlayer();
void startPlayer();

#ifdef GTEST
	extern int iCmdIndex;
	extern const char *apchBuff[10];
#endif

#ifdef __cplusplus
}
#endif

#endif /* CDPLAYER_H_ */
