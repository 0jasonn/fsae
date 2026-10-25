#ifndef WIP_A_CALLEES_H
#define WIP_A_CALLEES_H

// Prototypes and data symbols used by the round 13 implementer A files (src/wip/A). The reviewer moves the
// functions into engine/functions.h and the data into the shared data headers.
#include "types.h"

extern "C" {
// Mutex helpers (TwlSDK / NitroSDK).
void OS_LockMutexFromWToR(void *mutex);
void OS_UnlockMutex(void *mutex);

// Power management list helper (PMi_DeleteList(list, item)).
void PMi_DeleteList(void *list, void *item);

// String conversion helpers; they take five arguments and return a status.
u32 STD_ConvertStringSjisToUnicode(void *a, void *b, void *c, void *d, void *e);
u32 STD_ConvertStringUnicodeToSjis(void *a, void *b, void *c, void *d, void *e);

// Lock word and card bus helpers.
u32 OSi_DoTryLockByWord(void *word, u32 id, void *owner, u32 unused);
void OSi_FreeCardBus(void);
void OSi_AllocateCardBus(void);

// Interrupt and halt helpers.
u32 OS_EnableInterrupts(void);
u32 OS_DisableInterrupts(void);
void OS_RestoreInterrupts(u32 state);
void OS_Halt(void);

// VRAM bank helpers.
void resetBankForX_(void *bank);
}

extern u8 data_02129d94[];
extern u8 data_0212b924[];
extern u8 data_0212b93c[];
extern u8 data_02129872[];
extern u8 data_02129874[];
extern u8 data_0212986c[];
extern u8 data_0212986e[];
extern u8 data_0212987a[];
extern u8 data_0212987c[];

#endif
