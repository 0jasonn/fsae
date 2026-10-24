#ifndef WIP_F_UIOBJECT_H
#define WIP_F_UIOBJECT_H

// UIObject: one animated value (a position that moves from one point to another over a duration).
// Original class UIObject (0x58 bytes). Fields not yet used by the functions in uiobject.cpp are left as unk_.

#include "types.h"

// Animation curves of UIObject::movePos (the case numbers of its switch)
typedef enum AnimationCurve {
    ANIMATION_CURVE_LINER = 0,
    ANIMATION_CURVE_EASE_IN = 1,
    ANIMATION_CURVE_EASE_OUT = 2,
    ANIMATION_CURVE_NONE = 3
} AnimationCurve;

// Interpolates from[0..1] to to[0..1] at ratio (0x1000 = the end) into out[0..1]
typedef void (*UIObjectCalcFunc)(s32 *out, const s32 *from, const s32 *to, s32 ratio);

// Position pair used when the move result is copied
typedef struct UIPos2 {
    s32 x;
    s32 y;
} UIPos2;

typedef struct UIObject {
    /* 00 */ u8 kind; // set from the argument of UIObject_init
    /* 01 */ u8 active; // set to 1 by UIObject_init
    /* 02 */ u8 unk_02[3];
    /* 05 */ u8 frameCounter; // counts 0..0x77 and wraps, in UIObject_update
    /* 06 */ u8 unk_06[0x0a];
    /* 10 */ UIObjectCalcFunc calcFunc; // interpolation used by UIObject_updateMovePos
    /* 14 */ s32 fromX;
    /* 18 */ s32 fromY;
    /* 1c */ s32 toX;
    /* 20 */ s32 toY;
    /* 24 */ u8 unk_24[4];
    /* 28 */ s32 durationFP; // duration in frames << 12, 0 when no move is running
    /* 2c */ s32 elapsed; // time since the move started, same unit as durationFP >> 12
    /* 30 */ UIPos2 pos; // current position
    /* 38 */ u8 unk_38[0x50 - 0x38];
    /* 50 */ s32 unk_50;
    /* 54 */ void *unk_54;
} UIObject;

extern "C" {
void UIObject_movePos(UIObject *self, s32 x, s32 y, s32 duration, AnimationCurve curve);
BOOL UIObject_updateMovePos(UIObject *self, s32 step);
s32 UIObject_getDurationRatio(const UIObject *self);
BOOL UIObject_updateTime(UIObject *self, s32 step);
void UIObject_init(UIObject *self, u8 kind);
void calc_liner(s32 *out, const s32 *from, const s32 *to, s32 ratio);
void calc_easeIn(s32 *out, const s32 *from, const s32 *to, s32 ratio);
void calc_easeOut(s32 *out, const s32 *from, const s32 *to, s32 ratio);
}

#endif
