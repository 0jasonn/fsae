#include "engine/functions.h"
#include "global.h"

// Name plate actor (module nameplate). Address -> name:
//   0x0205b9a4 namePlate (original name), dispatches on e->action through namePlate_actions
//   namePlate_init at 0x0205b9c0 is in scratch/agentF/nonmatching/namePlate_init.c

typedef struct Vars_NamePlate {
    /* 00 */ u8 unk_00[0x64];
    /* 64 */ u8 unk_64[3];
    /* 67 */ u8 hideMask; // set to 0xff on init
} Vars_NamePlate;

extern const EntityFunc namePlate_actions[]; // namePlate_actions, indexed by e->action
extern u8 data_021349c0[];                   // byte 0x1b: flag that the name plate is shown

ARM void namePlate(Entity *e) {
    namePlate_actions[e->action](e);
}
