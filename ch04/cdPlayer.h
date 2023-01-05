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


typedef struct _State{
	const struct _State *(*stop)(const struct _State *pstState);
	const struct _State *(*playOrPause)(const struct _State *pstState);
}STATE;

void initialize();
void onStop();
void onPlayOrPause();

#ifdef GTEST
	extern int iCmdIndex;
	extern const char *apchBuff[10];
#endif

#ifdef __cplusplus
}
#endif

#endif /* CDPLAYER_H_ */
