#ifndef WIP_F_OPTION_H
#define WIP_F_OPTION_H

// Option panel screen (module option): shared state of the panel actors at 0x0205c03c..0x0205c3bb.
#include "engine/functions.h"
#include "global.h"
#include "object/fdecls.h"

// data_021349c0 bytes used by the option panels
enum {
    NP_PHASE = 0x1a,        // phase of the panel sequence, copied into the copy actor's subtimer
    NP_SHOWN = 0x1b,        // set to 1 by the panel actors on every frame they run
    NP_PANEL_STATE = 0x1c,  // bit 7: panel opening requested; low 2 bits: panel slot
    NP_HIDE_DONE = 0x1d,    // set to 1 when copy_hide has finished its animation
    NP_SLOT_B = 0x1f,       // slot of the second panel; 3 selects the mini panel patterns
    NP_CURSOR_COL = 0x02,   // cursor column, x = column * 16 + 0x18 (moji_cursor)
    NP_CURSOR_ROW = 0x03,   // cursor row, y = row * 16 + 0x35 (moji_cursor)
    NP_CURSOR_TYPE = 0x20,  // type compared with e->type2 by miniPanelPatSet
};

// Panel actor fields (file-local overlay of the copy actor)
typedef struct Vars_Option {
    /* 00 */ u8 unk_00[0x60];
    /* 60 */ u16 animBounds[2]; // bounds passed to ObjAnimMoveSet: x, then the second value
    /* 64 */ u8 patSelect;      // 0 or 1, added to patBase for unk_21
    /* 65 */ u8 patBase;        // pattern offset from copy_pattern_table
} Vars_Option;

extern u8 data_021349c0[];
extern const EntityFunc win_open_actions[];   // win_open_actions, indexed by e->action
extern const EntityFunc panel_copy_actions[]; // panel_copy_actions, indexed by e->action
extern const u16 win_open_table[];            // win_open_table, indexed by slot
extern const u8 data_020d8ac8[][6];           // animation bytes (shared with em1d_possess), row picked from data_021349c0[NP_PHASE]
extern u16 data_0212c75c[];                   // display shadow, halfword registers
extern const EntityFunc panel_mode_actions[]; // panel_mode_actions, indexed by e->action
extern u8 data_021348d8;                      // flag, nonzero: the panel moves the entity by 13 per type
extern u16 data_0212c594;                     // cursor counter, bits 2..4 pick the z offset
extern const s8 entry_z_table[];             // entry_z_table, z offsets for entry_cursor
extern u32 data_02171d20[];                   // resource ids, indexed by data_021349c0[NP_PHASE]

#define DISP_REG(off) data_0212c75c[(off) / 2]

void *KnifeApp_getInstance(void);

// data_021349c0 holds an Entity pointer at offset 8: the star entity moved by star_adjust
#define NP_ENTITY_PTR(off) (*(Entity **)(data_021349c0 + (off)))

void miniPanelPatSet(Entity *e);

#endif
