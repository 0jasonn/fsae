#include "engine/functions.h"
#include "global.h"
#include "object/setcommon.h"
#include "object/set09.h"

// Set09 actor (module set09). Address -> name:
//   0x02062bb8 Set09, 0x02062bd4 set09_init, 0x02062ce4 set09_wait, 0x02062d90 set09_initset,
//   0x02062dc4 set09_move, 0x02062e14 set09_wait2 (original names)

extern const EntityFunc data_020d9f38[]; // indexed by e->action
extern u32 em12_typeMasks[]; // one mask per area
void BgmSet(void);
void set6b_setenemy(Entity *e, u8 index);

void Set09(Entity *e) {
    data_020d9f38[e->action](e);
}
