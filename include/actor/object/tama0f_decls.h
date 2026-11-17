#ifndef WIP_TAMA0F_DECLS_H
#define WIP_TAMA0F_DECLS_H

#include "engine/functions.h"
#include "engine/player.h"
#include "actor/object/tama_decls.h"

// tama0f_ruppyset has an original (mangled) name: tama0f_ruppyset(OBJ_WORK_*, unsigned char).
void tama0f_ruppyset(Entity *e, u8 kind);

extern "C" {
void tama0f_contact(Entity *e);
}

#endif
