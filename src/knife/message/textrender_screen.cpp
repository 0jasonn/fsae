#include "engine/functions.h"
#include "global.h"
#include "game/decls_e.h"

// Functions in this file (plain names from the debug build, C linkage; the first argument is the TextRenderer):
//   func_020a59ac (0x020a59ac): screen buffer of the BG (isBg) or OBJ layer at index, from the screen buffer list or the
//   G2 / G2S screen pointer of that layer

extern "C" {
void *G2_GetBG0ScrPtr(void);
void *G2_GetBG1ScrPtr(void);
void *G2_GetBG2ScrPtr(void);
void *G2_GetBG3ScrPtr(void);
void *G2S_GetBG0ScrPtr(void);
void *G2S_GetBG1ScrPtr(void);
void *G2S_GetBG2ScrPtr(void);
void *G2S_GetBG3ScrPtr(void);
}

extern "C" void *func_020a59ac(Knife::Message::TextRenderer *self, s32 isBg, s32 index) {
    s32 layer = (isBg ? 0 : 4) + index;
    void *buffer = self->screenBuffer[layer];

    if (buffer != NULL) {
        return buffer;
    }
    switch (layer) {
    case 0:
        return G2_GetBG0ScrPtr();
    case 1:
        return G2_GetBG1ScrPtr();
    case 2:
        return G2_GetBG2ScrPtr();
    case 3:
        return G2_GetBG3ScrPtr();
    case 4:
        return G2S_GetBG0ScrPtr();
    case 5:
        return G2S_GetBG1ScrPtr();
    case 6:
        return G2S_GetBG2ScrPtr();
    case 7:
        return G2S_GetBG3ScrPtr();
    }
    return NULL;
}
