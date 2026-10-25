#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/pane.h"

// tween: functions TweenTable_noopA (0x020b6868), TweenTable_noopB (0x020b686c), Tween_init (0x020b6870) and
// Tween_initWithTable (0x020b6898), all matching. The table data_020deed4 is the table that TweenTable_noopA and
// TweenTable_noopB belong to (slots 1 and 2).

extern u8 data_020deed4[];

// TweenEntry: the record set up by Tween_init
typedef struct TweenEntry {
    u32 a;            // 0x00
    u32 b;            // 0x04
    u32 c;            // 0x08
    u8 flag;          // 0x0c
    u8 unk_0d[3];
    void *ptr10;      // 0x10
    void *ptr14;      // 0x14
} TweenEntry;

// TweenTable_noopA() (0x020b6868, provisional name): slot 1 of the table, does nothing
extern "C" void TweenTable_noopA(void);
ARM void TweenTable_noopA(void) {
}

// TweenTable_noopB() (0x020b686c, provisional name): slot 2 of the table, does nothing
extern "C" void TweenTable_noopB(void);
ARM void TweenTable_noopB(void) {
}

// Tween_init(self, a, b, c, flag, ptr14, ptr10) (0x020b6870, provisional name): stores the seven fields of the record
extern "C" void Tween_init(TweenEntry *self, u32 a, u32 b, u32 c, u32 flag, void *ptr14, void *ptr10);
ARM void Tween_init(TweenEntry *self, u32 a, u32 b, u32 c, u32 flag, void *ptr14, void *ptr10) {
    self->c = c;
    self->flag = flag;
    self->a = a;
    self->b = b;
    self->ptr14 = ptr14;
    self->ptr10 = ptr10;
}

// Tween_initWithTable(self, a, b, c, flag, ptr10) (0x020b6898, provisional name): Tween_init with the table data_020deed4
extern "C" void Tween_initWithTable(TweenEntry *self, u32 a, u32 b, u32 c, u32 flag, void *ptr10);
ARM void Tween_initWithTable(TweenEntry *self, u32 a, u32 b, u32 c, u32 flag, void *ptr10) {
    Tween_init(self, a, b, c, flag, data_020deed4, ptr10);
}
