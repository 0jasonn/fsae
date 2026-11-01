#ifndef GAME_RADAR_E_API_H
#define GAME_RADAR_E_API_H

// Functions defined in src/game/radar_e*.cpp.

#include "engine/entity.h"

extern "C" {
void draw_radar_defense(s32 mode, void *buf);
void draw_radar_goal_pos(s32 x, s32 y);
void draw_radar_kakera(s32 mode, void *buf);
void draw_radar_power(s32 mode, void *buf);
void draw_radar_speed(s32 mode, void *buf);
void draw_radar_time(s32 time, void *buf);
}

#endif
