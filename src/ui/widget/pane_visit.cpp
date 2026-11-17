#include "engine/functions.h"
#include "ui/widget/pane.h"

namespace {
class PaneVisitor {
public:
    virtual void *classInfo(void);
    virtual void release(void *arg);
    virtual void setOffset(void *ctx, void *delta);
    virtual void visit(void *arg);
};
}

// Provisional name. Visit the pane before recursively visiting its children.
void Pane_visitTree(void *obj, void *arg) {
    Pane *self = (Pane *)obj;
    s32 i;

    ((PaneVisitor *)self)->visit(arg);
    for (i = 0; i < self->childCount; i++) {
        Pane_visitTree(self->children[i], arg);
    }
}
