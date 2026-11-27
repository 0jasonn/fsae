#ifndef UI_VIEW_CONSTRUCTION_H
#define UI_VIEW_CONSTRUCTION_H

#include "ui/widget/baseduiview.h"

// Guard words shared by the original UI translation unit's local static views.
struct UIViewConstructionGuards {
    u32 groupCreateRoot;
    u32 fileSelectMode;
    u32 playStyleRoot;
    u32 modeSelectPlayStyle;
    u32 playStyleChild;
    u32 fileSelectRoot;
    u32 fileSelectChild;
    u32 groupCreateChild;
};

// Native construction type for the procedural PlayStyleSelUIView layout.
class playStyleSelUIView : public basedUIView {
public:
    void vfunc0();
    void vfunc1();
    void vfunc2();
    void enter();
    void leave();

    basedUIView *rootView;
    basedUIView *secondView;
    s32 unk_38;
    u8 unk_3c[0x5d - 0x3c];
    u8 unk_5d;
};

extern "C" {
extern UIViewConstructionGuards data_0217e2d4;
extern playStyleSelUIView data_0217e3d4;
}

#endif
