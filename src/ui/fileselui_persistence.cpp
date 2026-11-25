#include "engine/functions.h"
#include "ui/fileselui_view.h"

void fileSelUIView_serialize(FileSelUIView *self, u8 **buf) {
    self->objA->serialize(buf);
    self->objB->serialize(buf);
    self->objC->serialize(buf);

    MI_CpuCopy(&self->flag40, *buf, 1);
    *buf += 1;
    MI_CpuCopy(&self->flag41, *buf, 1);
    *buf += 1;
    MI_CpuCopy(&self->flag42, *buf, 1);
    *buf += 1;
    MI_CpuCopy(&self->flag43, *buf, 1);
    *buf += 1;
    MI_CpuCopy(&self->value48, *buf, 4);
    *buf += 4;
    MI_CpuCopy(self->block4c, *buf, 0x20);
    *buf += 0x20;
}

void fileSelUIView_deserialize(FileSelUIView *self, u8 **buf) {
    self->objA->deserialize(buf);
    self->objB->deserialize(buf);
    self->objC->deserialize(buf);

    MI_CpuCopy(*buf, &self->flag40, 1);
    *buf += 1;
    MI_CpuCopy(*buf, &self->flag41, 1);
    *buf += 1;
    MI_CpuCopy(*buf, &self->flag42, 1);
    *buf += 1;
    MI_CpuCopy(*buf, &self->flag43, 1);
    *buf += 1;
    MI_CpuCopy(*buf, &self->value48, 4);
    *buf += 4;
    MI_CpuCopy(*buf, self->block4c, 0x20);
    *buf += 0x20;
}
