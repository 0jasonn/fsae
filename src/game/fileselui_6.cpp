#include "engine/functions.h"
#include "global.h"

// Functions in this file (plain names from the debug build, C linkage):
//   fileSelUIView_viewDidDisapper (0x020a78f4)

void Knife_Message_CleanupTextRenderer(void); // C++, _Z33Knife_Message_CleanupTextRendererv, 0x020a2d30

// Pointers to the objects of the file select view (8 entries from +0x0c) and the index of the focused one (+0x2c)
typedef struct FileSelUIViewRefs {
    u8 unk_00[0x0c];
    void *objects[8];  // 0x0c
    s8 focus;          // 0x2c
} FileSelUIViewRefs;

// fileSelUIView::viewDidDisapper() (0x020a78f4): calls the virtual slot 4 of the focused object, then cleans up the
// text renderer
extern "C" void fileSelUIView_viewDidDisapper(void *a);
ARM void fileSelUIView_viewDidDisapper(void *a) {
    FileSelUIViewRefs *self = (FileSelUIViewRefs *)a;
    void *obj;
    void **vtbl;

    obj = self->objects[self->focus];
    vtbl = *(void ***)obj;
    ((void (*)(void *))vtbl[4])(obj);
    Knife_Message_CleanupTextRenderer();
}
