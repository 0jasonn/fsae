#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Record reader: src holds a pointer to a packed block whose first byte carries three flags (0x20, 0x40, 0x80). The
// second byte becomes the shifted 16-bit field at +0x68; func_0200b24c (Packed_readU32) reads the packed values that
// follow. The base value at +0x14 is copied to +0x18, or one of the alternates at +0x38 and +0x48 when the 0x40 flag
// is set (0x80 picks the first).
typedef struct PackedSrc {
    u8 unk_00[4];
    const u8 *data;          // 0x04
} PackedSrc;

typedef struct PackedRec {
    u8 unk_00[0x14];
    u32 base;                // 0x14
    u32 current;             // 0x18
    u8 unk_1c[0x1c];
    u32 alt1;                // 0x38
    u8 unk_3c[0x0c];
    u32 alt2;                // 0x48
    u8 unk_4c[0x14];
    u32 value1;              // 0x60
    u32 value2;              // 0x64
    u16 field68;             // 0x68
    u8 flag6a;               // 0x6a: bit 0x20 of the first byte
    u8 flag6b;               // 0x6b: bit 0x40 of the first byte
    u8 flag6c;               // 0x6c: bit 0x80 of the first byte
} PackedRec;

extern "C" const u8 *func_0200b24c(const u8 *src, u32 *value);

extern "C" void PackedRec_Parse(PackedRec *self, PackedSrc *src);

// Parses one record. The flags at +0x6a, +0x6b and +0x6c are the 0x20, 0x40 and 0x80 bits as 0 or 1.
ARM void PackedRec_Parse(PackedRec *self, PackedSrc *src) {
    const u8 *data;
    const u8 *p;
    u8 flags;

    data = src->data;
    flags = data[0];
    self->flag6b = (flags & 0x40) ? 1 : 0;
    self->flag6a = (flags & 0x20) ? 1 : 0;
    self->flag6c = (flags & 0x80) ? 1 : 0;
    self->field68 = data[1] << 4;
    self->field68 |= 0x4000;
    p = func_0200b24c(data + 2, &self->value1);
    if (flags & 0x40) {
        p = func_0200b24c(p, &self->value2);
    }
    if (flags & 0x40) {
        if (flags & 0x80) {
            self->current = self->alt1;
        } else {
            self->current = self->alt2;
        }
    } else {
        self->current = self->base;
    }
}
