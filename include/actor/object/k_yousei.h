#ifndef WIP_K_K_YOUSEI_H
#define WIP_K_K_YOUSEI_H

#include "engine/entity.h"

// Functions and data used by the K yousei file that no shared header declares yet.
u32 getRupeeLevel(void);       // 0x02082054, original getRupeeLevel()
void rupee_error(u16 message); // 0x02082094, original rupee_error(unsigned short)
void goto_nextdemo(void);      // 0x02082598, original goto_nextdemo()
int yousei_msgFinishWait(void); // 0x02082008, original msgFinishWait()
extern "C" {
int func_02081b64(void);       // 1 when every player has bit 0x200
void ClearKeyUpdate(u8 level); // 0x02048fa0, original ClearKeyUpdate(unsigned char)
}
extern u32 em12_typeMasks[];
extern u8 messageRequest[];
extern const u16 data_02117e10[]; // message ids of the fairy demo, indexed by gameState.unk_01

#endif
