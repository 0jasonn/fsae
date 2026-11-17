#include "knife/app/knife_power.h"

extern u8 data_021271c4[];

// Define the complete-object constructor entry explicitly to avoid an extra C2 variant.
void _ZN5Knife12PowerManagerC1Ev(Knife::PowerManager *self) {
    *(void **)self = data_021271c4;
    self->active = 0;
    self->sleepLockCount = 0;
    self->unk_0c = 1;
    self->unk_0d[0] = 0;
    self->unk_0d[1] = 0;
    self->unk_0d[2] = 0;
    self->unk_0d[3] = 0;
}
