#ifndef ENGINE_VGROUP_SLOTS_H
#define ENGINE_VGROUP_SLOTS_H

// Prototypes of the VGroup slot functions (C++ linkage, original signatures from original_names.tsv).
#include "engine/vgroup.h"

void setVGroup(Entity *e, VGROUP_ *group);
void createVGroup(VGROUP_ *first, u16 id, u8 count);
u8 countVGroupLine(u16 id); // 0x02081318, total slots of the request chain for an id

#endif
