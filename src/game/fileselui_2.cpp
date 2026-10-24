#include "engine/functions.h"
#include "global.h"
#include "game/fileselui.h"

// Functions in this file (original names from the debug build):
//   fileSelUIViewCtrl::serialize (0x020ad668), fileSelUIViewCtrl::deserialize (0x020ad6bc)

// fileSelUIViewCtrl::serialize (0x020ad668): writes the base view, then the two flag bytes
ARM void fileSelUIViewCtrl_serialize(FileSelUIViewCtrl *self, u8 **buf) {
    basedUIView_serialize((basedUIView *)self, buf);
    MI_CpuCopy(&self->unk_253c, *buf, 1);
    *buf += 1;
    MI_CpuCopy(&self->unk_253d, *buf, 1);
    *buf += 1;
}

// fileSelUIViewCtrl::deserialize (0x020ad6bc): reads back what serialize wrote
ARM void fileSelUIViewCtrl_deserialize(FileSelUIViewCtrl *self, u8 **buf) {
    basedUIView_deserialize((basedUIView *)self, buf);
    MI_CpuCopy(*buf, &self->unk_253c, 1);
    *buf += 1;
    MI_CpuCopy(*buf, &self->unk_253d, 1);
    *buf += 1;
}

// Frees a buffer pointer if it is set, then clears the pointer
#define FILESEL_FREE(ptr)         if ((ptr) != NULL) {              func_0208e188(ptr);           (ptr) = NULL;             }

// Frees the four buffers of a slot
#define FILESEL_FREE_SLOT(slot)            FILESEL_FREE((slot)->buf00);           FILESEL_FREE((slot)->buf08);           FILESEL_FREE((slot)->buf10);           FILESEL_FREE((slot)->buf18);

// fileSelUIViewCtrl::finalize (0x020ad710): releases the objects and buffers of the screen
ARM void fileSelUIViewCtrl_finalize(FileSelUIViewCtrl *self) {
    u32 i;
    void *oam;
    void *obj;
    FileSelSlot *slot;

    oam = self->oamBuffer;
    obj = self->unk_2540;
    if (oam != NULL) {
        func_0208e188(oam);
        self->oamBuffer = NULL;
    }
    subTask_free_objinfo((OBJInfo *)((u8 *)obj + 0x1c));
    subTask_free_objinfo((OBJInfo *)self->unk_2548);
    FILESEL_FREE(self->unk_26ac);
    FILESEL_FREE(self->unk_26b0);
    FILESEL_FREE(self->unk_26b4);
    for (i = 0; i < 4; i++) {
        subTask_free_slot(i);
        slot = &self->slotsA[i];
        FILESEL_FREE_SLOT(slot);
        slot = &self->slotsB[i];
        FILESEL_FREE_SLOT(slot);
    }
    func_0209bee4();
}
