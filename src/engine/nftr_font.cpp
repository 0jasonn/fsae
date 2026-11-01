#include "engine/functions.h"
#include "global.h"

// NftrFont_Relocate (provisional name, NftrFont_Relocate): relocates the NFTR font block at base. The records start at +0xc
// (halfword) and their count is at +0xe; each record has its tag at +0 and its stride at +4. Pointers of the FINF, CWDH and
// CMAP records are offsets from base and get base added (the zero ones stay zero where the record marks them optional).
extern "C" void NftrFont_Relocate(u8 *base);
ARM void NftrFont_Relocate(u8 *base) {
    u8 *rec;
    s32 i;
    s32 count;
    u32 tag;

    rec = base + *(u16 *)(base + 0xc);
    i = 0;
    count = *(u16 *)(base + 0xe);
    if (count <= 0) {
        return;
    }
    do {
        tag = *(u32 *)rec;
        switch (tag) {
        case 0x46494e46:
            *(u32 *)(rec + 0x10) += (u32)base;
            if (*(u32 *)(rec + 0x14) != 0) {
                *(u32 *)(rec + 0x14) += (u32)base;
            }
            if (*(u32 *)(rec + 0x18) != 0) {
                *(u32 *)(rec + 0x18) += (u32)base;
            }
            break;
        case 0x43574448:
            if (*(u32 *)(rec + 0xc) != 0) {
                *(u32 *)(rec + 0xc) += (u32)base;
            }
            break;
        case 0x434d4150:
            if (*(u32 *)(rec + 0x10) != 0) {
                *(u32 *)(rec + 0x10) += (u32)base;
            }
            break;
        case 0x43474c50:
            break;
        }
        rec += *(u32 *)(rec + 4);
        i++;
    } while (i < *(u16 *)(base + 0xe));
}
