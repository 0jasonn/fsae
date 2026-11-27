#include "ui/modeselui_view.h"

// Recognize standard non-allocating placement construction in this fixed storage.
#pragma use_simple_stdpnew on

inline void *operator new(size_t, void *storage) throw() {
    return storage;
}

void modeSelUIView_initialize(ModeSelUIView *self) {
    if ((data_0217e2d4.modeSelectPlayStyle & 1) == 0) {
        ::new (&data_0217e3d4) playStyleSelUIView;
        data_0217e2d4.modeSelectPlayStyle |= 1;
    }

    basedUIView_initialize(&self->base);
    self->child = &data_0217e3d4;
    self->unk_5b = 0;
    self->unk_5c = 0;
    self->unk_5f = 0;
    self->base.unk_04 = 1;
    self->child->vfunc0();
    self->unk_30 = 0;
}

#pragma use_simple_stdpnew reset
