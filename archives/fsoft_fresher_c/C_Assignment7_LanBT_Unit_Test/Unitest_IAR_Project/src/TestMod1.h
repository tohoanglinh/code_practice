#ifndef __MOD1TEST1_H__
#define __MOD1TEST1_H__

#include "common.h"

#define MAXDATA     10
#define LOWLIMIT    0
#define HIGHLIMIT   255
#define LOWTHHOLD   25
#define HITHHOLD    198

#define CNT10M      10

extern  BYTE gu8TurnData[MAXDATA];
extern  BYTE gu8HighAveTurnData;
extern  BYTE gu8LowAveTurnData;

extern  void Mod1_Init(void);
extern  void Mod1_Test10mTask(void);
extern  void Mod1_SetTurnData(BYTE data);


#endif


