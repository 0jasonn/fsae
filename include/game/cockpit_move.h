#ifndef GAME_COCKPIT_MOVE_H
#define GAME_COCKPIT_MOVE_H

#include "engine/entity.h"

// cockpit_move (original cockpit_move()) and the callees below keep their original C++ names:
// kattiUpdate(), rupeeUpdate(), heartUpdate(unsigned short), heartAlart(), make_item_color(), make_item_char(),
// make_item_color_2p(), make_item_char_2p()
void cockpit_move(void);
extern "C" {
void EffectSet(Entity *e, int kind, int arg);
}
void kattiUpdate(void);
void rupeeUpdate(void);
void heartUpdate(u16 kind);
void heartAlart(void);
void make_item_color(void);
void make_item_char(void);
void make_item_color_2p(void);
void make_item_char_2p(void);

#endif
