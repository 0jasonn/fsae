#ifndef WIP_C_TAMA_DECLS_H
#define WIP_C_TAMA_DECLS_H

// Declarations used by the tama actor files in src/wip/C that are not in engine/functions.h yet.

#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"

extern "C" {
void func_0208af0c(Entity *e);
void func_0208b668(Entity *e);
u8 ObjGetDir2(Entity *e, Entity *target, s32 a, s32 b); // 0x0204fdfc, unmangled
int func_02085764(Entity *a, Entity *b, s32 c, s32 d); // 0x02085764, thumb, returns a flag
}

typedef struct TamaTelopIds { u16 ids[3]; } TamaTelopIds;
extern const TamaTelopIds data_020dcb60;
extern const TamaTelopIds data_020dcb68;
extern const EntityFunc data_020dcb48[];
extern const EntityFunc data_020dcb74[];
extern const EntityFunc data_020dcb88[];
extern const u8 data_020dcb1b[];
extern const void *const data_02117b90[];
extern const u8 data_020dcb13[];
extern const u8 data_020dcb10[];
extern const u8 data_020dcb17[];
extern const u16 data_020dcb28[];
extern s32 em2e_type4Hidden; // 0x021348c8, bss flag set by em2e

#endif
