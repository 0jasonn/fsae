#ifndef WIP_F_BASEDUIVIEW_H
#define WIP_F_BASEDUIVIEW_H

// basedUIView: a screen of the touch UI. Each view is a C++ object with a vtable (slot 3 = enter, slot 4 = leave)
// and keeps a stack of child views in the view that owns them.

#include "types.h"

class basedUIView {
public:
    virtual void vfunc0(void); // vtable slots 0 to 2 are not used by the functions in baseduiview.cpp
    virtual void vfunc1(void);
    virtual void vfunc2(void);
    virtual void enter(void); // vtable slot 3
    virtual void leave(void); // vtable slot 4

    /* 04 */ u32 unk_04; // set to 7 by basedUIView_initialize, serialized
    /* 08 */ basedUIView *parent;
    /* 0c */ basedUIView *viewStack[8];
    /* 2c */ s8 stackIndex; // index of the top view in viewStack
};

extern "C" {
void MI_CpuCopy(const void *src, void *dst, u32 size);
void basedUIView_initialize(basedUIView *self);
void basedUIView_setRootView(basedUIView *self, basedUIView *root);
void basedUIView_push_view(basedUIView *self, basedUIView *child);
void basedUIView_pop_view(basedUIView *self);
void basedUIView_serialize(basedUIView *self, u8 **buf);
void basedUIView_deserialize(basedUIView *self, u8 **buf);
}

#endif
