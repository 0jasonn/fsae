#ifndef WIP_E_TEMPLATE_H
#define WIP_E_TEMPLATE_H

// Actor-template table: data_0212ced8 holds one 0x94-byte entry per type; the first word of an entry is a pointer
// to the template Entity that new objects copy their start-up state from. Shared by the arrow and bomb units.
#include "engine/entity.h"

extern u8 data_0212ced8[];
#define OBJ_TEMPLATE(type) (*(Entity **)(data_0212ced8 + (type) * 0x94))

#endif
