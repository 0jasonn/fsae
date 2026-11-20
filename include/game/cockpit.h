#ifndef GAME_COCKPIT_H
#define GAME_COCKPIT_H

// Cockpit (HUD) callees of the E units that functions.h does not declare yet.
#include "engine/functions.h"
#include "game/cockpitdata.h"

void CockpitUpdate(void);                // original CockpitUpdate()
void cockpit_obj_set(u8 index);          // original cockpit_obj_set(unsigned char)
void bg_trans_body(void);                // original bg_trans_body()
extern "C" void func_02027778(void);     // dsd name, empty function (bx lr), symbol is plain
void heart_disp(void);
void kakera_disp(void);                  // original kakera_disp()
void kinomi_write(void);                 // original kinomi_write()                   // original heart_disp()
void rupee_disp(void);                   // original rupee_disp()
void addrupee_disp(void);                // original addrupee_disp()

void BgmSet(void);
// cockpit_move() and its callees (original C++ names): kattiUpdate(), rupeeUpdate(), heartUpdate(unsigned short),
// heartAlart(), make_item_color(), make_item_char(), make_item_color_2p(), make_item_char_2p()
void cockpit_move(void);                 // 0x02026e4c
void kattiUpdate(void);
void rupeeUpdate(void);
void heartUpdate(u16 kind);
void heartAlart(void);
void make_item_color(void);
void make_item_char(void);
void make_item_color_2p(void);
void make_item_char_2p(void);
void cockpit_write_rupee(u16 *dst, u32 value, u8 count, u16 flags); // original write_rupee, cockpit_6.cpp                       // original BgmSet()
extern "C" u32 func_020867cc(void);     // dsd name, thumb function (0x020867cc), plain symbol
extern "C" {
void CockpitInit(void);
}

// Declared here for the reviewer to move into engine/functions.h (original CockpitRecovery(unsigned char, unsigned char)).
void CockpitRecovery(u8 kind, u8 amount);

#endif
