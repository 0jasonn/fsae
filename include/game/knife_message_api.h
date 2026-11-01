#ifndef GAME_KNIFE_MESSAGE_API_H
#define GAME_KNIFE_MESSAGE_API_H

// Functions defined in src/game/knife_message*.cpp.

#include "engine/entity.h"

extern "C" {
void Knife_Message_KnifeInfoGetter_noop(void *a);
void Knife_Message_MessageTextRender_initWithCanvas(void *self, void *a, void *b, u16 c, u32 d, u32 e, u32 f, u32 g);
void Knife_Message_MessageTextRender_onReadNop(void *a);
void func_020a0dc0(void);
void func_020a0dc4(void);
void func_020a0dc8(void);
void func_020a0ed4(void);
void func_020a0ed8(void);
void func_020a1100(void *self, u8 value);
void func_020a1108(void *self, u8 value);
void func_020a1330(void);
void func_020a1334(void);
void func_020a1338(void);
void func_020a133c(void);
void func_020a1600(void);
void func_020a1604(void);
void func_020a1608(void);
void func_020a160c(void);
void func_020a1610(void);
void func_020a237c(void);
void func_020a2380(void);
void func_020a2384(void);
void func_020a2388(void);
void func_020a238c(void);
void func_020a2390(void);
void func_020a2394(void);
void func_020a2398(void);
void func_020a239c(void);
void func_020a23a0(void);
void func_020a23a4(void);
void func_020a23a8(void);
void func_020a23ac(void);
void func_020a23b0(void);
void func_020a23b4(void);
void func_020a23b8(void);
}

#endif
