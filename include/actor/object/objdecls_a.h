#ifndef WIP_A_DECLS_H
#define WIP_A_DECLS_H

// Functions called by implementer A's files that are not in engine/functions.h yet.
// Original signatures from config/eur/original_names.tsv (or the dsd name where no original is known).
// Move these into functions.h when integrating.
#include "engine/functions.h"

void ZeldaFadeSet(Entity *e, u32 mode);                 // ZeldaFadeSet(OBJ_WORK_*, unsigned long), 0x0205b67c
void InitCircleWindow(u16 a, u16 b);                    // InitCircleWindow(unsigned short, unsigned short), 0x0202b5d4
void MakeCircleWindow(s16 x, s16 y, s16 radius);        // MakeCircleWindow(short, short, short), 0x0202b620
void StopEffectWindow(void);                            // StopEffectWindow(), 0x0202b598
Entity *GetSetWorkSp(u8 a, u8 b, u8 c);                 // GetSetWorkSp(unsigned char, unsigned char, unsigned char), 0x02076898
void breakset(Entity *e);                               // breakset(OBJ_WORK_*), 0x0206a964
int func_02083ed8(Entity *e, Entity *other);            // dsd name, C++ linkage, 0x02083ed8
void func_0208366c(s32 a, u16 b, u16 c);                // _Z13func_0208366cltt (dsd name), 0x0208366c
extern "C" void func_0208af0c(Entity *e);               // plain dsd name, 0x0208af0c

extern "C" void AddHeart(Entity *e, int amount);        // plain name, no original parameters listed (0x02025d9c)
void AddHeartUtsuwa(u8 type, s8 amount);                // AddHeartUtsuwa(unsigned char, signed char), 0x0202604c

#endif
