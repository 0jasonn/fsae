#ifndef WIP_F_OPTION_H
#define WIP_F_OPTION_H

// Option panel screen (module option): shared state of the panel actors at 0x0205c03c..0x0205c3bb.
#include "engine/functions.h"
#include "global.h"
#include "actor/object/fdecls.h"

// Panel actor fields (file-local overlay of the copy actor)
typedef struct Vars_Option {
    /* 00 */ u8 unk_00[0x60];
    /* 60 */ u16 animBounds[2]; // bounds passed to ObjAnimMoveSet: x, then the second value
    /* 64 */ u8 patSelect;      // 0 or 1, added to patBase for unk_21
    /* 65 */ u8 patBase;        // pattern offset from copy_pattern_table
} Vars_Option;

#include "engine/effect_state.h"
extern const EntityFunc win_open_actions[];   // win_open_actions, indexed by e->action
extern const EntityFunc panel_copy_actions[]; // panel_copy_actions, indexed by e->action
extern const u16 win_open_table[];            // win_open_table, indexed by slot
extern const u8 data_020d8ac8[][6];           // animation bytes (shared with em1d_possess), row picked from effectState.panelPhase
#include "engine/display_state.h"
extern const EntityFunc panel_mode_actions[]; // panel_mode_actions, indexed by e->action
extern u8 data_021348d8;                      // flag, nonzero: the panel moves the entity by 13 per type
extern const s8 entry_z_table[];             // entry_z_table, z offsets for entry_cursor
extern u32 data_02171d20[];                   // resource ids, indexed by effectState.panelPhase

void *KnifeApp_getInstance(void);

void miniPanelPatSet(Entity *e);

#endif
