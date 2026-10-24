#include "engine/functions.h"
#include "global.h"
#include "game/baseduiview.h"

// Functions in this file (original names from the debug build):
//   basedUIView::initialize (0x020acd98), setRootView (0x020acdb0), push_view (0x020acdd8), pop_view (0x020ace40),
//   serialize (0x020ace9c), deserialize (0x020acf5c)

// basedUIView::initialize (0x020acd98): empty stack, no parent
ARM void basedUIView_initialize(basedUIView *self) {
    self->unk_04 = 7;
    self->parent = NULL;
    self->stackIndex = 0;
}

// basedUIView::setRootView (0x020acdb0): the root view becomes the bottom of the stack and is entered
ARM void basedUIView_setRootView(basedUIView *self, basedUIView *root) {
    self->viewStack[0] = root;
    self->stackIndex = 0;
    root->parent = self;
    root->enter();
}

// basedUIView::push_view (0x020acdd8): leaves the top view, pushes child and enters it
ARM void basedUIView_push_view(basedUIView *self, basedUIView *child) {
    self->viewStack[self->stackIndex]->leave();
    self->viewStack[self->stackIndex]->parent = NULL;
    self->stackIndex++;
    self->viewStack[self->stackIndex] = child;
    child->parent = self;
    child->enter();
}

// basedUIView::pop_view (0x020ace40): leaves the top view, removes it and enters the view below
ARM void basedUIView_pop_view(basedUIView *self) {
    self->viewStack[self->stackIndex]->leave();
    self->viewStack[self->stackIndex]->parent = NULL;
    self->stackIndex--;
    self->viewStack[self->stackIndex]->enter();
}

// basedUIView::serialize (0x020ace9c): writes unk_04, parent, stackIndex and the views below the top to the buffer
ARM void basedUIView_serialize(basedUIView *self, u8 **buf) {
    u32 i;
    u32 parent;
    void *entry;

    MI_CpuCopy(&self->unk_04, *buf, 4);
    *buf += 4;
    parent = (u32)self->parent;
    MI_CpuCopy(&parent, *buf, 4);
    *buf += 4;
    MI_CpuCopy(&self->stackIndex, *buf, 1);
    *buf += 1;
    for (i = 0; i < self->stackIndex; i++) {
        entry = self->viewStack[i];
        MI_CpuCopy(&entry, *buf, 4);
        *buf += 4;
    }
}

// basedUIView::deserialize (0x020acf5c): reads back what serialize wrote
ARM void basedUIView_deserialize(basedUIView *self, u8 **buf) {
    u32 i;
    u32 parent;
    void *entry;

    MI_CpuCopy(*buf, &self->unk_04, 4);
    *buf += 4;
    MI_CpuCopy(*buf, &parent, 4);
    *buf += 4;
    self->parent = (basedUIView *)parent;
    MI_CpuCopy(*buf, &self->stackIndex, 1);
    *buf += 1;
    for (i = 0; i < self->stackIndex; i++) {
        MI_CpuCopy(*buf, &entry, 4);
        *buf += 4;
        self->viewStack[i] = (basedUIView *)entry;
    }
}
