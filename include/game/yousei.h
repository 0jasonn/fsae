#ifndef GAME_YOUSEI_H
#define GAME_YOUSEI_H

#include "engine/entity.h"

// Calls used by the yousei files that engine/functions.h does not declare yet (reviewer: move them to functions.h).
int yousei_msgFinishWait(void);              // 0x02082008, 1 while a player's message window is still open
extern "C" int func_02081b64(void);           // 0x02081b64 (src/game/yousei.cpp), 1 when every player has bit 0x200
extern "C" void ComRequest(u8 request);       // original ComRequest(unsigned char)
extern "C" void YouseiDemoLoad(void);                    // original YouseiDemoLoad()
void demolink_set(void);                      // original demolink_set()
int ZeldaFadeFlagGet(void);                   // 0x0205b6f0, no original name (symbol _Z16ZeldaFadeFlagGetv)
void goto_nextdemo(void);      // 0x02082598, original goto_nextdemo()

#endif
