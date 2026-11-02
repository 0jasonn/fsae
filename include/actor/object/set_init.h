#ifndef WIP_C_SET_INIT_H
#define WIP_C_SET_INIT_H

#include "engine/entity.h"

// Actor setup tables: 3 u16 per record (sprite info, color info, value for Entity::unk_1b).
// spriteInfo 0: nothing, bit 15 set: sprite flags in Entity::unk_20, otherwise a VGroup id; 0xfffe skips the setup, 0xffff redirects
// to setInitSubTables[colorInfo], indexed by the actor type.
// colorInfo bit 15 set: palette index in the low bits (0x80ff keeps the current one), otherwise an object color id.
extern const u16 setInitTable[];                // 0x020dc340, indexed by Entity::objId
extern const u16 *const setInitSubTables[];     // 0x020dc1d0

void SetInit(Entity *e); // 0x02057614

#endif
