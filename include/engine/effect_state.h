#ifndef ENGINE_EFFECT_STATE_H
#define ENGINE_EFFECT_STATE_H

#include "types.h"

struct OBJ_WORK_;

// Effect/result state block (effectState, 0x28 bytes up to data_021349e8). It is scratch work shared by the scene
// sequences: ending_init, op_init, DemoTask and ranking_init clear all 0x28 bytes, and every scene uses its own subset
// of the bytes, so some offsets are read with different widths by different scenes (hence the unions).
// dsd also has the symbols data_021349d8 (+0x18, rankValues) and data_021349e6 (+0x26, tenkuScroll) inside this block.
typedef struct EffectState {
    /* 00 */ u8 phase;      // scene state machine (ending scenes, op_scene_*, gufu_body_move, title: 2 = save data check)
    /* 01 */ u8 subPhase;   // sub-state of demo_00/demo_01; read by Set6a and sr_main
    /* 02 */ u8 selection;  // selected entry: door select, cursor, lr_cursor, door_silver; moji_cursor column
    /* 03 */ u8 entryCount; // door select: number of entries; moji_cursor row
    /* 04 */ u16 timer;     // frames left in the current phase (counted down by most scenes, up by a few)
    /* 06 */ u16 messageIndex; // stage select: message/dialog index (also indexes the message frame table); title: cleared
    /* 08 */ union {
        struct {
            /* 08 */ u8 progress;   // title: menu progress (bit 7, low nibble from opTitleState) read by cursor, lever,
                                    // key, door_silver; yousei: clear level from ClearKeyCheck; door select: restart flag
            /* 09 */ u8 stepTimer;  // opening: frames before stepIndex advances; key_pos_set: scale
            /* 0a */ u8 stepIndex;  // opening: index into mistStepTable (0xff at the end); key: position offset;
                                    // stage select: nonzero spawns the 0x46 actors again
            /* 0b */ u8 fadeActive; // opening: set once the mist steps are done, color_control runs while set
        };
        struct OBJ_WORK_ *star; // option screen: star entity moved by star_adjust (set by star_cursor)
    };
    /* 0c */ union {
        struct {
            /* 0c */ u8 fadeStep;   // 0..0x10, scaled by 0x10 for the fade buffers (ending, opening)
            /* 0d */ u8 subState;   // opening scene sub-state (op_scene_01, gufu_hand_move)
            /* 0e */ u8 sceneFlag;  // opening: set by the scenes (2..5), gufu_body_move switches on it
            /* 0f */ u8 activeSlot; // opening: fairy talk slot of the running effect, 0xff when none
        };
        u32 playerFlags; // ranking: bit per player, set once that player's result is shown
    };
    /* 10 */ u32 finishedCount; // ranking: number of players whose result was shown
    /* 14 */ u8 restoreFlag;    // set02: nonzero puts the actor back into the work list
    /* 15 */ u8 dialogShown;    // stage select: cleared by stagesel_dialogDelete
    /* 16 */ u8 dialogSound;    // stage select: nonzero while the dialog sound plays
    /* 17 */ u8 unk_17;
    /* 18 */ union {
        u16 rankValues[4]; // ranking: values written by calc_result (dsd symbol data_021349d8)
        struct {
            /* 18 */ u8 unk_18[2];
            /* 1a */ u8 panelPhase; // option/name plate: phase of the panel sequence (3 while the plate is set up)
            /* 1b */ u8 panelShown; // option/name plate: set to 1 by the panel actors on every frame they run
            /* 1c */ u8 panelState; // option: bit 7 panel opening requested, low 2 bits panel slot (bar master slot type)
            /* 1d */ u8 hideDone;   // option: set to 1 when copy_hide has finished its animation
            /* 1e */ u8 slotA;      // name plate: slot index of the first plate
            /* 1f */ u8 slotB;      // name plate/option: slot of the second panel; 3 selects the mini panel patterns
        };
    };
    /* 20 */ union {
        u32 scrollWork; // stage select: word written by stagesel_init/stagesel_move, read by stagesel_scroll
        struct {
            /* 20 */ u8 cursorType; // option: type compared with e->type2 by miniPanelPatSet and change_panel
            /* 21 */ u8 unk_21;
            /* 22 */ u8 entryIndex; // option: entry_cursor position (x = entryIndex * 8 + 0x24, 6 or more: 0x4c)
            /* 23 */ u8 unk_23;
        };
    };
    /* 24 */ union {
        u32 frames; // ending: incremented once per frame by ending_rescue and finale_demo
        struct {
            /* 24 */ u8 panelMode; // option/name plate: nonzero draws the plate at the second position, 2 hides it
            /* 25 */ u8 unk_25;
            /* 26 */ union {
                s16 tenkuScroll; // stage select: scroll offset added to the tenku_kumo actors (dsd symbol data_021349e6)
                struct {
                    /* 26 */ u8 unk_26;
                    /* 27 */ u8 removeFlag; // ranking: nonzero removes the plate and rupee actors
                };
            };
        };
    };
} EffectState;
extern EffectState effectState; // 0x021349c0

#endif
